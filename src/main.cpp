#include "server/Server.hpp"

int main() {
    // Start server on port 6379 (standard Redis port)
    Server server(6379);
    server.run();
    return 0;
}
