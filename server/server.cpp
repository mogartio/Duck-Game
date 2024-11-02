#include "server.h"

#include <list>
#include <utility>

#include "game_logic/game_main.h"
// is_testing sirve para testear cosas del juego a mano
Server::Server(const char* port, bool is_testing):
        srv(port), clients(), recv_queue(100), send_queues(), is_testing(is_testing) {}

void Server::run() {
    GameMain game(recv_queue, "juancito", "pedrito", is_testing, send_queues);
    game.start();
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    // pongo a correr el thread que lee input (TEMPORAL)
    ReadInput read_input_t;
    // read_input_t.start();
    while (read_input_t.is_alive()) {
        std::list<GenericMsg*> msgs;
        GenericMsg* msg;
        while (recv_queue.try_pop(msg)) {
            // std::cout << "\n" << "Mensaje del cliente recibido: " << std::endl;
            // msg->print_info();
        }
        send_queues.broadcast(msgs);
    }
    acceptor.stop();
    acceptor.join();
    read_input_t.join();
    game.join();
}
