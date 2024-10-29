#ifndef SERVER_H
#define SERVER_H
#include <string>

#include "acceptor.h"
#include "clients_monitor.h"
#include "read_input.h"
#include "send_queues_monitor.h"

class Server {
private:
    Socket srv;
    ClientsMonitor clients;
    Queue<GenericMsg*> recv_queue;
    SendQueuesMonitor<GenericMsg*> send_queues;

public:
    explicit Server(const char* port);
    void run();
};
#endif
