#include "server.h"

#include <list>
#include <utility>

Server::Server(const char* port): srv(port), clients(), recv_queue(100), send_queues() {}

void Server::run() {
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    // pongo a correr el thread que lee input (TEMPORAL)
    ReadInput read_input_t;
    read_input_t.start();
    std::cout << "Server levantado" << std::endl;
    ErrorMsg msg1("Error en el server!!!!!!!");
    while (read_input_t.is_alive()) {
        std::list<GenericMsg*> msgs;
        GenericMsg* msg;
        while (recv_queue.try_pop(msg)) {
            msg->print_info();
            msgs.push_back(&msg1);
        }
        send_queues.broadcast(msgs);
    }
    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}
