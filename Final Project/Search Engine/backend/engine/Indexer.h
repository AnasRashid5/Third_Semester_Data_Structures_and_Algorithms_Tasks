#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <unordered_map>
#include <vector>

// ISSUE FIX: Avoids importing the whole std namespace into every file that includes this header.
class Indexer
{
private:
    // word -> { file_path -> frequency_count }
    std::unordered_map<std::string, std::unordered_map<std::string, int>> relations;

public:
    void storeRelations(const std::string &filePath,
                        const std::vector<std::string> &words);
    void printRelations();

    const std::unordered_map<std::string, int> &getDocumentsForWord(
        const std::string &word);
};

#endif
