#include "acceptor.h"

Acceptor::Acceptor(Socket srv, ClientsMonitor& clients, Queue<std::string>& recv_queue, SendQueuesMonitor& send_queues) 
    : srv(std::move(srv)), clients(clients), recv_queue(recv_queue), send_queues(send_queues) {}

void Acceptor::run() {
    try {
        while (_keep_running) {
            Socket new_client = srv.accept();

            Queue<std::string>* new_send_queue = new Queue<std::string>(Q_MAX_SIZE);
            send_queues.add(new_send_queue);

            Client client(std::move(new_client), *new_send_queue, recv_queue);
            clients.add(client);

            reap_dead_clients();
        }
    } catch (const std::exception& e) {
        _keep_running = false;
    }
}

void Acceptor::reap_dead_clients() {
    clients.remove_dead_clients();
}

void Acceptor::stop() {
    srv.shutdown(2);
    _keep_running = false;
    recv_queue.close();
}

void Acceptor::shutdown() {
    clients.remove_all();
    send_queues.remove_all();
}