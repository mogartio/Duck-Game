#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <list>
#include <utility>

#include <sys/socket.h>

#include "client.h"
#include "lobbys_monitor.h"
#include "send_queues_monitor.h"

class Acceptor: public Thread {
private:
    Socket srv;
    std::list<Client> clients;
    SendQueuesMonitor<GenericMsg*> send_queues;
    LobbysMonitor lobbys;
    bool is_testing;

    void run() override;

    void reap_dead_clients();

    void acceptClient(uint& id);

    void remove_all();

    const int Q_MAX_SIZE = 100;

public:
    explicit Acceptor(const char* port, bool);

    void stop() override;

    void shutdown();
};

#endif
