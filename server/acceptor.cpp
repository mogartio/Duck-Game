#include "acceptor.h"


Acceptor::Acceptor(const char* port): srv(port) {}

void Acceptor::acceptClient(uint& id) {
    Socket new_skt = srv.accept();
    clients.emplace_back(std::move(new_skt), id, send_queues, lobbys);
}

void Acceptor::run() {
    try {
        uint id = 1;
        while (_keep_running) {
            acceptClient(id);

            reap_dead_clients();

            id++;
        }
    } catch (const std::exception& e) {
        _keep_running = false;
    }
}

void Acceptor::reap_dead_clients() {
    clients.remove_if([](Client& client) {
        if (!client.is_alive()) {
            client.stop();
            return true;
        }
        return false;
    });
}

void Acceptor::remove_all() {
    for (Client& client: clients) {
        client.stop();
    }
    clients.clear();
}

void Acceptor::stop() {
    srv.shutdown(SHUT_RDWR);
    _keep_running = false;
    remove_all();
}

void Acceptor::shutdown() {
    remove_all();
    send_queues.remove_all();
}
