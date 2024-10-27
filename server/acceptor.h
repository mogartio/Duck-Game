#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <string>

#include "../common/queue.h"
#include "../common/socket/socket.h"
#include "../common/thread.h"
#include "../common/messages/generic_msg.h"

#include "client.h"
#include "clients_monitor.h"
#include "send_queues_monitor.h"
#include <utility>
#include <sys/socket.h>

class Acceptor: public Thread {
private:
    Socket srv;
    ClientsMonitor& clients;
    Queue<GenericMsg*>& recv_queue;
    SendQueuesMonitor<GenericMsg*>& send_queues;

    void run() override;
    
    void reap_dead_clients();

    const int Q_MAX_SIZE = 100;

public:
    Acceptor(Socket srv, ClientsMonitor& clients, Queue<GenericMsg*>& recv_queue,
             SendQueuesMonitor<GenericMsg*>& send_queues);

    void stop() override;
    
    void shutdown();

};

#endif
