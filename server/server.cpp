#include "server.h"

Server::Server(const char* port) : srv(port), clients(), recv_queue(), send_queues() {}

void Server::run() {
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    // pongo a correr el thread que lee input (TEMPORAL)
    ReadInput read_input_t;
    read_input_t.start();

    while(read_input_t.is_alive()) {
        std::cout << "Server running??" << std::endl;
    }

    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}