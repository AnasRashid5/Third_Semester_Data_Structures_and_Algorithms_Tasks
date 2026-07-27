#include "Indexer.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

// unordered_map<string, unordered_set<string>> relations;

void Indexer::storeRelations(const string &filePath, const vector<string> &words)
{
    int i = 0;

    // ISSUE FIX: Compares signed index with size() without a signed/unsigned mismatch warning.
    while (i < static_cast<int>(words.size()))
    {
        // relations[words[i]].insert(filePath);
        relations[words[i]][filePath]++;
        i++;
    }
}

void Indexer::printRelations()
{
    for (const auto &pair : relations)
    {
        const string &word = pair.first;
        const auto &docPairs = pair.second;
        cout << word << "-> ";
        // Loop through the documents for this specific word
        for (const auto &docPair : docPairs)
        {
            const string &filePath = docPair.first;
            const int &count = docPair.second;
            cout << "[" << filePath << " (Count: " << count << ")] ";
        }
        cout << endl;
    }
}

const unordered_map<string, int> &Indexer::getDocumentsForWord(const string &word)
{
    auto it = relations.find(word);
    if (it != relations.end())
    {
        return it->second;
    }

    // Static empty map optimization for safe reference returns
    static const unordered_map<string, int> emptyMap;
    return emptyMap;
}