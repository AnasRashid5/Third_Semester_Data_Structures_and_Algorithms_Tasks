#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

// ISSUE FIX: Avoids importing the whole std namespace into every file that includes this header.
struct Trie_Node
{
    bool isEndOfWord;
    Trie_Node *children[26];
};

class Trie
{
private:
    Trie_Node *root;

    Trie_Node *insert(Trie_Node *current, const std::string &word, int index);
    Trie_Node *findPrefix(Trie_Node *current, const std::string &prefix, int index);
    void collectWords(Trie_Node *current, std::string word,
                      std::vector<std::string> &suggestions, int limit);
    void clear(Trie_Node *current);

public:
    Trie();
    ~Trie();

    void insert(const std::string &word);
    std::vector<std::string> autocomplete(const std::string &prefix, int limit = 10);
};

#endif
