#include "SearchEngine.h"
#include "../engine/Parser.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

SearchEngine::SearchEngine(Indexer &idx) : indexer(idx) {}

unordered_set<string> SearchEngine::getIntersection(
    const unordered_set<string> &set1, const unordered_set<string> &set2)
{
    unordered_set<string> result;

    for (const string &doc : set1)
    {
        if (set2.count(doc))
        {
            result.insert(doc);
        }
    }

    return result;
}

unordered_set<string> SearchEngine::getUnion(
    const unordered_set<string> &set1, const unordered_set<string> &set2)
{
    unordered_set<string> result = set1;

    for (const string &doc : set2)
    {
        result.insert(doc);
    }

    return result;
}

vector<SearchResult> SearchEngine::search(const string &query, string &message)
{
    Parser parser;
    vector<string> tokens = parser.parseQuery(query);
    vector<SearchResult> rankedResults;

    if (tokens.empty())
    {
        message = "Empty query.";
        return rankedResults;
    }

    vector<string> cleanedTokens;

    for (int i = 0; i < static_cast<int>(tokens.size()); ++i)
    {
        bool isOperator = (tokens[i] == "and" || tokens[i] == "or");

        if ((i == 0 || i == static_cast<int>(tokens.size()) - 1) && isOperator)
        {
            continue;
        }

        if (isOperator)
        {
            bool previousIsOperator = i > 0 &&
                (tokens[i - 1] == "and" || tokens[i - 1] == "or");
            bool nextIsOperator = i + 1 < static_cast<int>(tokens.size()) &&
                (tokens[i + 1] == "and" || tokens[i + 1] == "or");

            if (previousIsOperator || nextIsOperator)
            {
                continue;
            }
        }

        cleanedTokens.push_back(tokens[i]);
    }

    tokens = cleanedTokens;

    if (tokens.empty())
    {
        message = "No matching documents found.";
        return rankedResults;
    }

    bool hasAnd = false;
    bool hasOr = false;
    vector<string> validTokens;

    for (const string &token : tokens)
    {
        if (token == "and")
        {
            hasAnd = true;
        }
        else if (token == "or")
        {
            hasOr = true;
        }
        else
        {
            validTokens.push_back(token);
        }
    }

    if (hasAnd && hasOr)
    {
        message = "Mixed AND/OR queries are not supported.";
        return rankedResults;
    }

    if (validTokens.empty())
    {
        message = "No matching documents found.";
        return rankedResults;
    }

    unordered_set<string> candidateDocs;

    if (hasOr)
    {
        for (const string &token : validTokens)
        {
            unordered_set<string> currentDocs;
            const auto &docs = indexer.getDocumentsForWord(token);

            for (const auto &pair : docs)
            {
                currentDocs.insert(pair.first);
            }

            candidateDocs = getUnion(candidateDocs, currentDocs);
        }
    }
    else
    {
        bool firstWord = true;

        for (const string &token : validTokens)
        {
            unordered_set<string> currentDocs;
            const auto &docs = indexer.getDocumentsForWord(token);

            for (const auto &pair : docs)
            {
                currentDocs.insert(pair.first);
            }

            if (firstWord)
            {
                candidateDocs = currentDocs;
                firstWord = false;
            }
            else
            {
                candidateDocs = getIntersection(candidateDocs, currentDocs);

                if (candidateDocs.empty())
                {
                    break;
                }
            }
        }
    }

    unordered_map<string, int> scores;

    for (const string &doc : candidateDocs)
    {
        for (const string &token : validTokens)
        {
            const auto &docs = indexer.getDocumentsForWord(token);
            auto foundDocument = docs.find(doc);

            if (foundDocument != docs.end())
            {
                scores[doc] += foundDocument->second;
            }
        }
    }

    for (const auto &pair : scores)
    {
        rankedResults.push_back({pair.first, pair.second});
    }

    sort(rankedResults.begin(), rankedResults.end(),
        [](const SearchResult &a, const SearchResult &b)
        {
            if (a.score == b.score)
            {
                return a.document < b.document;
            }

            return a.score > b.score;
        });

    if (rankedResults.empty())
    {
        message = "No matching documents found.";
    }
    else
    {
        message = "Search complete.";
    }

    return rankedResults;
}

void SearchEngine::executeQuery(const string &query)
{
    string message;
    vector<SearchResult> rankedResults = search(query, message);

    if (rankedResults.empty())
    {
        cout << message << endl;
        return;
    }

    cout << "\nResults:\n" << endl;

    for (int i = 0; i < static_cast<int>(rankedResults.size()); ++i)
    {
        cout << i + 1 << ". " << rankedResults[i].document
             << "    Score: " << rankedResults[i].score << endl;
    }
}
