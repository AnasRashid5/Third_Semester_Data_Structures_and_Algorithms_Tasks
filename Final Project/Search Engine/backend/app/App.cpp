// #include "App.h"
// #include "../engine/Parser.h"
// #include "../engine/Indexer.h"
// #include "../engine/SearchEngine.h"
// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;

// void App::run()
// {
//     Parser parser;
//     Indexer indexer;

//     string testPath = "storage/documents/doc1.txt";
//     string testPath2 = "storage/documents/doc2.txt";

//     cout << "Parsing file: " << testPath << endl;
//     vector<string> result = parser.parseFile(testPath);

//     cout << "Parsing file: " << testPath2 << endl;
//     vector<string> result2 = parser.parseFile(testPath2);

//     cout << "Found " << result.size() << " clean words:" << endl;
//     for (const string &word : result)
//     {
//         cout << "[" << word << "] ";
//     }
//     cout << endl;
//     for (const string &word : result2)
//     {
//         cout << "[" << word << "] ";
//     }

//     cout << endl
//          << endl;
//     indexer.storeRelations(testPath, result);
//     indexer.storeRelations(testPath2, result2);
//     // indexer.printRelations();

//     SearchEngine searchEngine(indexer);

//     // 3. User Input Loop
//     string query;
//     while (true)
//     {
//         cout << "\nEnter search query (or type 'exit' to quit): ";
//         getline(cin, query); // Takes the raw query right here in App

//         if (query == "exit")
//         {
//             break;
//         }

//         // Pass the raw query directly to the engine
//         searchEngine.executeQuery(query);
//     }
// }

#include "App.h"
#include "../engine/Parser.h"
#include "../engine/Indexer.h"
#include "../engine/SearchEngine.h"
#include "../ds/Stack.h"
#include "../ds/Trie.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

void App::run()
{
    Parser parser;
    Indexer indexer;

    string testPath = "storage/documents/doc1_search_engines_overview.txt";
    string testPath2 = "storage/documents/doc2_machine_learning_intro.txt";

    // ISSUE FIX: Supports running the program from either the backend folder or project folder.
    if (!filesystem::exists(testPath))
    {
        testPath = "backend/storage/documents/doc1_search_engines_overview.txt";
        testPath2 = "backend/storage/documents/doc2_machine_learning_intro.txt";
    }

    cout << "Parsing file: " << testPath << endl;
    vector<string> result = parser.parseFile(testPath);

    cout << "Parsing file: " << testPath2 << endl;
    vector<string> result2 = parser.parseFile(testPath2);

    cout << "Found " << result.size() << " clean words:" << endl;
    for (const string &word : result)
    {
        cout << "[" << word << "] ";
    }
    cout << endl;
    for (const string &word : result2)
    {
        cout << "[" << word << "] ";
    }

    cout << endl
         << endl;
    indexer.storeRelations(testPath, result);
    indexer.storeRelations(testPath2, result2);

    Trie autocompleteTrie;
    for (const string &word : result)
    {
        autocompleteTrie.insert(word);
    }
    for (const string &word : result2)
    {
        autocompleteTrie.insert(word);
    }

    // indexer.printRelations();

    
    cout << "--- ENGINE STATUS CHECK ---" << endl;
    if (result.empty() && result2.empty())
    {
        cout << "[WARNING] Parsed words list is empty! Check relative file paths for doc1.txt / doc2.txt." << endl;
    }
    else
    {
        cout << "[SUCCESS] Documents parsed & indexed successfully." << endl;
    }

    // Test automated sample query before opening user prompt
    SearchEngine searchEngine(indexer);

    if (!result.empty())
    {
        cout << "\n--- AUTOMATED TEST QUERY ---" << endl;
        cout << "Testing search for word: '" << result[0] << "'" << endl;
        searchEngine.executeQuery(result[0]);
    }
    cout << "----------------------------\n"
         << endl;
    // =========================================================

    // 3. User Input Loop
    string query;
    vector<string> searchHistory;
    while (true)
    {
        cout << "\nEnter search query ('autocomplete', 'history', or 'exit'): ";
        getline(cin, query); // Takes the raw query right here in App

        if (query == "exit")
        {
            break;
        }

        const string autocompleteCommand = "autocomplete ";
        if (query.rfind(autocompleteCommand, 0) == 0)
        {
            vector<string> suggestions = autocompleteTrie.autocomplete(
                query.substr(autocompleteCommand.length()));

            if (suggestions.empty())
            {
                cout << "No suggestions found." << endl;
            }
            else
            {
                cout << "\nSuggestions:" << endl;
                for (const string &suggestion : suggestions)
                {
                    cout << "- " << suggestion << endl;
                }
            }
            continue;
        }

        if (query == "history")
        {
            vector<int> historyIndexes = getStackValues();

            if (historyIndexes.empty())
            {
                cout << "No search history yet." << endl;
                continue;
            }

            cout << "\nSearch history (newest first):" << endl;
            for (int index : historyIndexes)
            {
                cout << "- " << searchHistory[index] << endl;
            }
            continue;
        }

        if (query.empty())
        {
            cout << "Empty query." << endl;
            continue;
        }

        searchHistory.push_back(query);
        push(static_cast<int>(searchHistory.size() - 1));

        // Pass the raw query directly to the engine
        searchEngine.executeQuery(query);
    }

    clearStack();
}