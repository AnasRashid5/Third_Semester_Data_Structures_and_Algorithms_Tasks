#include "WebServer.h"
#include "../engine/Parser.h"

#include <filesystem>
#include <iostream>

using namespace std;

WebServer::WebServer() : searchEngine(indexer)
{
    // ISSUE FIX: Supports starting the server from either project folder.
    if (filesystem::exists("frontend/index.html"))
    {
        frontendDirectory = "frontend";
    }
    else
    {
        frontendDirectory = "../frontend";
    }

    loadDocuments();
}

void WebServer::loadDocuments()
{
    Parser parser;
    filesystem::path documentsDirectory = "backend/storage/documents";

    // ISSUE FIX: Uses the correct document location when launched inside backend.
    if (!filesystem::is_directory(documentsDirectory))
    {
        documentsDirectory = "storage/documents";
    }

    if (!filesystem::is_directory(documentsDirectory))
    {
        cerr << "Warning: documents folder was not found." << endl;
        return;
    }

    int indexedFiles = 0;

    // ISSUE FIX: Indexes every .txt file in storage so the corpus can grow without code changes.
    for (const filesystem::directory_entry &entry :
         filesystem::directory_iterator(documentsDirectory))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        if (entry.path().extension() != ".txt")
        {
            continue;
        }

        const string documentPath = entry.path().string();
        vector<string> words = parser.parseFile(documentPath);

        if (words.empty())
        {
            cerr << "Warning: no words parsed from " << documentPath << endl;
            continue;
        }

        indexer.storeRelations(documentPath, words);

        for (const string &word : words)
        {
            autocompleteTrie.insert(word);
        }

        indexedFiles++;
        cout << "Indexed " << words.size() << " words from " << documentPath << endl;
    }

    if (indexedFiles == 0)
    {
        cerr << "Warning: no .txt documents were indexed. "
             << "Run the server from the project root or the backend folder." << endl;
    }
    else
    {
        cout << "Search index ready: " << indexedFiles << " document(s)." << endl;
    }
}
