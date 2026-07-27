#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "../ds/Trie.h"
#include "../engine/Indexer.h"
#include "../engine/SearchEngine.h"

#include <string>

class WebServer
{
private:
    Indexer indexer;
    Trie autocompleteTrie;
    SearchEngine searchEngine;
    std::string frontendDirectory;

    void loadDocuments();

public:
    WebServer();
    void run(int port = 8080);
};

#endif
