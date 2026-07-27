#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "../engine/Indexer.h"
#include <string>
#include <unordered_set>
#include <vector>

struct SearchResult
{
    std::string document;
    int score;
};

class SearchEngine
{
private:
    Indexer &indexer;

    std::unordered_set<std::string> getIntersection(
        const std::unordered_set<std::string> &set1,
        const std::unordered_set<std::string> &set2);
    std::unordered_set<std::string> getUnion(
        const std::unordered_set<std::string> &set1,
        const std::unordered_set<std::string> &set2);

public:
    SearchEngine(Indexer &idx);

    // ISSUE FIX: Returns structured results so the website can receive JSON.
    std::vector<SearchResult> search(const std::string &query, std::string &message);

    // ISSUE FIX: Keeps the original console output available for the CLI version.
    void executeQuery(const std::string &query);
};

#endif
