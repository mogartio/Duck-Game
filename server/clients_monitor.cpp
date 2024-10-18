#include "clients_monitor.h"

ClientsMonitor::ClientsMonitor(): m(), clients() {}

void ClientsMonitor::add(Client& client) {
    std::lock_guard<std::mutex> lock(m);
    clients.push_back(client);
}

void ClientsMonitor::remove(Client& client) {
    std::lock_guard<std::mutex> lock(m);
    clients.remove(client);
}

