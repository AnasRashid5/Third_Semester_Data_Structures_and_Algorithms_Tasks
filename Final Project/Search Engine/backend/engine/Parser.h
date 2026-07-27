#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

// ISSUE FIX: Avoids importing the whole std namespace into every file that includes this header.
class Parser
{
public:
    std::vector<std::string> parseFile(const std::string &filePath);
    std::vector<std::string> parseQuery(const std::string &query);
};

#endif
