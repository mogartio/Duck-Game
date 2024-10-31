#include "acceptor.h"


Acceptor::Acceptor(Socket srv, ClientsMonitor& clients, Queue<GenericMsg*>& recv_queue,
                   SendQueuesMonitor<GenericMsg*>& send_queues):
        srv(std::move(srv)), clients(clients), recv_queue(recv_queue), send_queues(send_queues) {}


void Acceptor::run() {
    try {
        int id = 0;
        while (_keep_running) {
            Socket new_skt = srv.accept();

            Queue<GenericMsg*>* new_send_queue = new Queue<GenericMsg*>(Q_MAX_SIZE);
            send_queues.add(new_send_queue, id);

            Client* client = new Client(std::move(new_skt), new_send_queue, &recv_queue, id++);
            clients.add(client);

            reap_dead_clients();
        }
    } catch (const std::exception& e) {
        _keep_running = false;
    }
}

void Acceptor::reap_dead_clients() { clients.remove_dead_clients(); }

void Acceptor::stop() {
    srv.shutdown(SHUT_RDWR);
    _keep_running = false;
    recv_queue.close();
}

void Acceptor::shutdown() {
    clients.remove_all();
    send_queues.remove_all();
}
