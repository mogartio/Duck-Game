#include "server.h"

#include <list>
#include <utility>

#include "game_logic/game_main.h"

Server::Server(const char* port): srv(port), clients(), recv_queue(100), send_queues() {}

void Server::run() {
    Queue<GenericMsg*> q(1000);
    GameMain game(q);
    game.run();
    // // pongo a correr el acceptor
    // Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    // acceptor.start();
    // // pongo a correr el thread que lee input (TEMPORAL)
    // ReadInput read_input_t;
    // read_input_t.start();
    // while (read_input_t.is_alive()) {
    //     std::list<GenericMsg*> msgs;
    //     GenericMsg* msg;
    //     while (recv_queue.try_pop(msg)) {
    //         // std::cout << "\n" << "Mensaje del cliente recibido: " << std::endl;
    //         // msg->print_info();
    //     }
    //     send_queues.broadcast(msgs);
    // }
    // acceptor.stop();
    // acceptor.join();
    // read_input_t.join();
}
