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

void ClientsMonitor::remove_dead_clients() {
    std::lock_guard<std::mutex> lock(m);
    clients.remove_if([](Client& client) {
        if (!client.is_alive()) {
            client.stop();
            return true;
        }
        return false;
    });
}

void ClientsMonitor::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    for (Client& client : clients) {
        client.stop();
    }
    clients.clear();
}