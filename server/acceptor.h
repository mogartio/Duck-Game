#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/queue.h"
#include "client.h"
#include "clients_monitor.h"
#include "send_queues_monitor.h"

class Acceptor : public Thread {
private: 
    Socket srv;
    ClientsMonitor& clients;
    Queue<std::string>& recv_queue;
    SendQueuesMonitor<std::string>& send_queues;

    void run() override;
    void reap_dead_clients();

    const int Q_MAX_SIZE = 100;
public:
    Acceptor(Socket srv, ClientsMonitor& clients, Queue<std::string>& recv_queue, SendQueuesMonitor<std::string>& send_queues);

    void stop() override;
    void shutdown();
};

#endif