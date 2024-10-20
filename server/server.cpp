#include "server.h"

Server::Server(const char* port) : srv(port){}

void Server::run() {
    SendQueuesMonitor<std::string> send_queues_dummy;
    Queue<std::string> recv_queue_dummy;
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue_dummy, send_queues_dummy);
    acceptor.start();

    // pongo a correr el thread que maneja el lobby manager
    // pongo a correr la lectura del input (TEMPORAL)
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        if (input == "q") {
            acceptor.stop();
            acceptor.join();
        }
    }
}
