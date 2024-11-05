#ifndef SERVER_H
#define SERVER_H
#include <string>

#include "acceptor.h"

class Server {
private:
    const char* port;
    bool is_testing;
    bool _keep_running;

public:
    explicit Server(const char* port, bool is_testing);
    void run();
};
#endif
