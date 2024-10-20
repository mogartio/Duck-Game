#ifndef SERVER_H
#define SERVER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/queue.h"
#include "./../common/mensaje-lobby.h"
#include "client.h"
#include "clients_monitor.h"
#include "send_queues_monitor.h"
#include "acceptor.h"

class Server {
private:
    Socket srv;
    ClientsMonitor clients;
    Queue<MensajeLobby> recv_queue; // Pongo std::string pero va a cambiar segun el protocolo
    SendQueuesMonitor<MensajeLobby> send_queues;
public:
    explicit Server(const char* port);
    void run();
};

#endif
