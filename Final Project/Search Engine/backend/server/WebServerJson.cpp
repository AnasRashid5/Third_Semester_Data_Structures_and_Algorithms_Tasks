#include "WebServerJson.h"

#include <iomanip>
#include <sstream>

using namespace std;

namespace
{
// ISSUE FIX: Escapes all JSON-special characters so API responses never break parsing in the browser.
string escapeJson(const string &text)
{
    string escaped;

    for (unsigned char character : text)
    {
        switch (character)
        {
        case '\\':
        case '"':
            escaped += '\\';
            escaped += static_cast<char>(character);
            break;
        case '\b':
            escaped += "\\b";
            break;
        case '\f':
            escaped += "\\f";
            break;
        case '\n':
            escaped += "\\n";
            break;
        case '\r':
            escaped += "\\r";
            break;
        case '\t':
            escaped += "\\t";
            break;
        default:
            if (character < 0x20)
            {
                ostringstream code;
                code << "\\u" << setfill('0') << setw(4) << hex
                     << static_cast<int>(character);
                escaped += code.str();
            }
            else
            {
                escaped += static_cast<char>(character);
            }
            break;
        }
    }

    return escaped;
}
}

// ISSUE FIX: Converts the C++ search results into data JavaScript can use.
string makeSearchJson(const vector<SearchResult> &results, const string &message)
{
    ostringstream json;
    json << "{\"message\":\"" << escapeJson(message) << "\",\"results\":[";

    for (int i = 0; i < static_cast<int>(results.size()); ++i)
    {
        if (i > 0)
        {
            json << ",";
        }

        json << "{\"document\":\"" << escapeJson(results[i].document)
             << "\",\"score\":" << results[i].score << "}";
    }

    json << "]}";
    return json.str();
}

string makeSuggestionsJson(const vector<string> &suggestions)
{
    ostringstream json;
    json << "{\"suggestions\":[";

    for (int i = 0; i < static_cast<int>(suggestions.size()); ++i)
    {
        if (i > 0)
        {
            json << ",";
        }

        json << "\"" << escapeJson(suggestions[i]) << "\"";
    }

    json << "]}";
    return json.str();
}
