#include "Trie.h"

#include <cctype>

// ISSUE FIX: Keep this namespace import inside the implementation file only.
using namespace std;

Trie::Trie()
{
    root = nullptr;
}

Trie::~Trie()
{
    clear(root);
}

Trie_Node *Trie::insert(Trie_Node *current, const string &word, int index)
{
    if (current == nullptr)
    {
        Trie_Node *temp = new Trie_Node;
        temp->isEndOfWord = false;

        for (int i = 0; i < 26; i++)
        {
            temp->children[i] = nullptr;
        }

        current = temp;
    }

    if (index == static_cast<int>(word.length()))
    {
        current->isEndOfWord = true;
        return current;
    }

    int childIndex = word[index] - 'a';

    if (childIndex < 0 || childIndex >= 26)
    {
        return current;
    }

    current->children[childIndex] =
        insert(current->children[childIndex], word, index + 1);

    return current;
}

void Trie::insert(const string &word)
{
    root = insert(root, word, 0);
}

Trie_Node *Trie::findPrefix(Trie_Node *current, const string &prefix, int index)
{
    if (current == nullptr)
    {
        return nullptr;
    }

    if (index == static_cast<int>(prefix.length()))
    {
        return current;
    }

    int childIndex = prefix[index] - 'a';

    if (childIndex < 0 || childIndex >= 26)
    {
        return nullptr;
    }

    return findPrefix(current->children[childIndex], prefix, index + 1);
}

void Trie::collectWords(Trie_Node *current, string word,vector<string> &suggestions, int limit)
{
    if (current == nullptr || static_cast<int>(suggestions.size()) >= limit)
    {
        return;
    }

    // Like preorder traversal: process the current node, then its children.
    if (current->isEndOfWord)
    {
        suggestions.push_back(word);
    }

    for (int i = 0; i < 26; i++)
    {
        if (current->children[i] != nullptr)
        {
            char nextCharacter = 'a' + i;
            collectWords(current->children[i], word + nextCharacter,
                         suggestions, limit);
        }
    }
}

vector<string> Trie::autocomplete(const string &prefix, int limit)
{
    string cleanPrefix = "";

    // ISSUE FIX: Converts input safely so uppercase browser input matches the lowercase Trie.
    for (unsigned char character : prefix)
    {
        if (isalpha(character))
        {
            cleanPrefix += static_cast<char>(tolower(character));
        }
    }

    vector<string> suggestions;

    if (cleanPrefix.empty() || limit <= 0)
    {
        return suggestions;
    }

    Trie_Node *prefixNode = findPrefix(root, cleanPrefix, 0);

    if (prefixNode == nullptr)
    {
        return suggestions;
    }

    collectWords(prefixNode, cleanPrefix, suggestions, limit);
    return suggestions;
}

void Trie::clear(Trie_Node *current)
{
    if (current == nullptr)
    {
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        clear(current->children[i]);
    }

    delete current;
}
