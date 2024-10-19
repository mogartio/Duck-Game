#ifndef CLIENTS_MONITOR_H
#define CLIENTS_MONITOR_H

#include <mutex>
#include <list>
#include <string>
#include "../common/queue.h"
#include "client.h"

class ClientsMonitor {
private:
    std::mutex m;
    std::list<Client*> clients;

public:
    ClientsMonitor();

    void add(Client* client);
    void remove(Client* client);
    void remove_dead_clients();
    void remove_all();
};

#endif // CLIENTS_MONITOR_H