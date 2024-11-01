#include "server.h"

#include <list>
#include <utility>

// is_testing sirve para testear cosas del juego a mano
Server::Server(const char* port, bool is_testing):
        srv(port), clients(), recv_queue(100), send_queues(), is_testing(is_testing) {}

void Server::run() {

    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    // pongo a correr el thread que lee input (TEMPORAL)
    ReadInput read_input_t;
    // read_input_t.start();
    read_input_t.start();

    WinnerMsg msg1("Candela");
    UpdatedPlayerInfoMsg msg2("Candela", std::make_pair(1, 1), 1, 1);

    while (read_input_t.is_alive()) {
        std::list<GenericMsg*> msgs;
        GenericMsg* msg;
        while (recv_queue.try_pop(msg)) {
            std::cout  << "Mensaje recibido con header: 0x" << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(msg->get_header())<< std::endl;
            msgs.push_back(&msg1);
            msgs.push_back(&msg2);
        }
        send_queues.broadcast(msgs);
    }
    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}
