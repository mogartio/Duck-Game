#include "server.h"

Server::Server(const char* port) : srv(port), clients(), recv_queue(), send_queues() {}

void Server::run() {
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    // pongo a correr el thread que lee input (TEMPORAL)
    ReadInput read_input_t;
    read_input_t.start();
    std::cout << "Server levantado" << std::endl;
    while(read_input_t.is_alive()) {
        std::list<std::string> msgs;
        std::string msg;
        while(recv_queue.try_pop(msg)) {
            msgs.push_back(msg);
        }
        for (auto& msg : msgs) {
            std::cout << "Received message: " << msg << std::endl;
        } 
        send_queues.broadcast(msgs);
    }

    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}