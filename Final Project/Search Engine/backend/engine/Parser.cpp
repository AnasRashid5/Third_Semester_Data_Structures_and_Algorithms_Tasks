#include "Parser.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// ISSUE FIX: Uses unsigned characters before ctype checks to avoid undefined behavior.
string cleanSingleWord(const string &word)
{
    string cleanWord = "";

    for (unsigned char character : word)
    {
        if (!ispunct(character))
        {
            cleanWord += static_cast<char>(tolower(character));
        }
    }

    return cleanWord;
}

vector<string> Parser::parseFile(const string &filePath)
{
    vector<string> tokens;
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file at " << filePath << endl;
        return tokens;
    }

    string line;
    while (getline(file, line))
    {
        stringstream lineStream(line);
        string word;

        while (lineStream >> word)
        {
            string cleanWord = cleanSingleWord(word);

            if (!cleanWord.empty())
            {
                tokens.push_back(cleanWord);
            }
        }
    }

    return tokens;
}

vector<string> Parser::parseQuery(const string &query)
{
    vector<string> tokens;
    stringstream queryStream(query);
    string word;

    // ISSUE FIX: Uses stream extraction instead of indexing one character past the query.
    while (queryStream >> word)
    {
        string cleanWord = cleanSingleWord(word);

        if (!cleanWord.empty())
        {
            tokens.push_back(cleanWord);
        }
    }

    return tokens;
}
