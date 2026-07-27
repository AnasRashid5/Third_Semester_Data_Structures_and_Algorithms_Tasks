#include "WebServer.h"
#include "WebServerJson.h"

// ISSUE FIX: Uses Winsock instead of cpp-httplib so the project builds reliably on Windows without huge-header OOM failures.
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

namespace
{
string urlDecode(const string &value)
{
    string decoded;

    for (size_t i = 0; i < value.size(); ++i)
    {
        if (value[i] == '+')
        {
            decoded += ' ';
        }
        else if (value[i] == '%' && i + 2 < value.size())
        {
            auto hexDigit = [](char c) -> int
            {
                if (c >= '0' && c <= '9')
                {
                    return c - '0';
                }
                if (c >= 'a' && c <= 'f')
                {
                    return 10 + c - 'a';
                }
                if (c >= 'A' && c <= 'F')
                {
                    return 10 + c - 'A';
                }
                return -1;
            };

            int high = hexDigit(value[i + 1]);
            int low = hexDigit(value[i + 2]);

            if (high >= 0 && low >= 0)
            {
                decoded += static_cast<char>((high << 4) | low);
                i += 2;
            }
            else
            {
                decoded += value[i];
            }
        }
        else
        {
            decoded += value[i];
        }
    }

    return decoded;
}

unordered_map<string, string> parseQueryString(const string &query)
{
    unordered_map<string, string> params;
    stringstream stream(query);
    string pair;

    while (getline(stream, pair, '&'))
    {
        if (pair.empty())
        {
            continue;
        }

        size_t equalSign = pair.find('=');
        if (equalSign == string::npos)
        {
            params[urlDecode(pair)] = "";
        }
        else
        {
            params[urlDecode(pair.substr(0, equalSign))] =
                urlDecode(pair.substr(equalSign + 1));
        }
    }

    return params;
}

bool parseRequestLine(const string &request, string &method, string &path, string &query)
{
    stringstream stream(request);
    string version;
    stream >> method >> path >> version;

    if (method.empty() || path.empty())
    {
        return false;
    }

    size_t questionMark = path.find('?');
    if (questionMark != string::npos)
    {
        query = path.substr(questionMark + 1);
        path = path.substr(0, questionMark);
    }
    else
    {
        query.clear();
    }

    return true;
}

void sendResponse(SOCKET client, int statusCode, const string &statusText,
                  const string &contentType, const string &body,
                  const vector<pair<string, string>> &extraHeaders = {})
{
    ostringstream response;
    response << "HTTP/1.1 " << statusCode << ' ' << statusText << "\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << body.size() << "\r\n";
    response << "Connection: close\r\n";

    for (const auto &header : extraHeaders)
    {
        response << header.first << ": " << header.second << "\r\n";
    }

    response << "\r\n" << body;

    const string payload = response.str();
    send(client, payload.c_str(), static_cast<int>(payload.size()), 0);
}

string readStaticFile(const filesystem::path &filePath)
{
    ifstream file(filePath, ios::binary);
    if (!file.is_open())
    {
        return "";
    }

    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string contentTypeForPath(const string &path)
{
    if (path.size() >= 5 && path.substr(path.size() - 5) == ".html")
    {
        return "text/html; charset=utf-8";
    }
    if (path.size() >= 4 && path.substr(path.size() - 4) == ".css")
    {
        return "text/css; charset=utf-8";
    }
    if (path.size() >= 3 && path.substr(path.size() - 3) == ".js")
    {
        return "application/javascript; charset=utf-8";
    }

    return "application/octet-stream";
}

bool isSafeRelativePath(const string &path)
{
    return !path.empty() && path[0] == '/' && path.find("..") == string::npos;
}
}

void WebServer::run(int port)
{
#ifndef _WIN32
    cerr << "This web server build targets Windows (Winsock)." << endl;
    return;
#else
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "Could not initialize Winsock." << endl;
        return;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        cerr << "Could not create socket." << endl;
        WSACleanup();
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(static_cast<u_short>(port));
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    int reuseAddress = 1;
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR,
               reinterpret_cast<const char *>(&reuseAddress), sizeof(reuseAddress));

    if (bind(listenSocket, reinterpret_cast<sockaddr *>(&address), sizeof(address)) == SOCKET_ERROR)
    {
        cerr << "Could not bind to port " << port << ". Is another server already running?" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cerr << "Could not listen on port " << port << "." << endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    cout << "Search website running at http://localhost:" << port << endl;
    cout << "Open that URL in your browser (do not open index.html as a file)." << endl;

    while (true)
    {
        SOCKET client = accept(listenSocket, nullptr, nullptr);
        if (client == INVALID_SOCKET)
        {
            continue;
        }

        char buffer[8192] = {};
        int received = recv(client, buffer, sizeof(buffer) - 1, 0);

        if (received <= 0)
        {
            closesocket(client);
            continue;
        }

        string method;
        string path;
        string query;
        if (!parseRequestLine(buffer, method, path, query))
        {
            sendResponse(client, 400, "Bad Request", "text/plain", "Bad request.");
            closesocket(client);
            continue;
        }

        if (method != "GET")
        {
            sendResponse(client, 405, "Method Not Allowed", "text/plain", "Only GET is supported.");
            closesocket(client);
            continue;
        }

        const unordered_map<string, string> params = parseQueryString(query);

        // ISSUE FIX: Added Access-Control-Allow-Origin header so browsers do not
        // block fetch('/api/autocomplete') with a CORS error when the page is
        // opened from a different origin during development or testing.
        if (path == "/api/autocomplete")
        {
            const string prefix = params.count("prefix") ? params.at("prefix") : "";
            sendResponse(client, 200, "OK", "application/json; charset=utf-8",
                         makeSuggestionsJson(autocompleteTrie.autocomplete(prefix)),
                         {{"Access-Control-Allow-Origin", "*"}});
        }
        // ISSUE FIX: Added endpoint to serve document contents directly to the frontend.
        else if (path == "/api/document")
        {
            const string docPath = params.count("name") ? params.at("name") : "";
            
            // Prevent directory traversal attacks
            if (docPath.find("..") == string::npos && filesystem::is_regular_file(docPath))
            {
                const string body = readStaticFile(docPath);
                sendResponse(client, 200, "OK", "text/plain; charset=utf-8", body,
                             {{"Access-Control-Allow-Origin", "*"}});
            }
            else
            {
                sendResponse(client, 404, "Not Found", "text/plain", "Document not found.",
                             {{"Access-Control-Allow-Origin", "*"}});
            }
        }
        // ISSUE FIX: Same CORS header applied to the search endpoint so that
        // JavaScript fetch('/api/search') is always allowed by the browser.
        else if (path == "/api/search")
        {
            const string searchQuery = params.count("q") ? params.at("q") : "";
            string message;
            vector<SearchResult> results = searchEngine.search(searchQuery, message);
            sendResponse(client, 200, "OK", "application/json; charset=utf-8",
                         makeSearchJson(results, message),
                         {{"Access-Control-Allow-Origin", "*"}});
        }
        // ISSUE FIX: Serve index.html content directly for the root path instead
        // of issuing a 302 redirect to /index.html. The redirect caused some
        // browsers to cache the redirect itself and also created an extra round-trip.
        else if (path == "/")
        {
            const filesystem::path indexPath =
                filesystem::path(frontendDirectory) / "index.html";
            const string body = readStaticFile(indexPath);
            if (body.empty())
            {
                sendResponse(client, 404, "Not Found", "text/plain", "index.html not found.");
            }
            else
            {
                sendResponse(client, 200, "OK", "text/html; charset=utf-8", body);
            }
        }
        else if (isSafeRelativePath(path))
        {
            const filesystem::path filePath =
                filesystem::path(frontendDirectory) / path.substr(1);

            if (filesystem::is_regular_file(filePath))
            {
                const string body = readStaticFile(filePath);
                // ISSUE FIX: Added Cache-Control: no-cache so the browser always
                // re-validates static assets (CSS, JS) after a rebuild, preventing
                // users from seeing a stale version of app.js or style.css.
                sendResponse(client, 200, "OK", contentTypeForPath(path), body,
                             {{"Cache-Control", "no-cache"}});
            }
            else
            {
                sendResponse(client, 404, "Not Found", "text/plain", "Not found.");
            }
        }
        else
        {
            sendResponse(client, 404, "Not Found", "text/plain", "Not found.");
        }

        closesocket(client);
    }

    closesocket(listenSocket);
    WSACleanup();
#endif
}
