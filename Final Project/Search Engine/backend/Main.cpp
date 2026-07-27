#include "server/WebServer.h"

int main()
{
    // ISSUE FIX: The program now starts a web server instead of only a console loop.
    WebServer server;
    server.run();
    return 0;
}
