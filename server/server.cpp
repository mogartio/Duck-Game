#include "server.h"

#include <list>
#include <utility>

#include "game_logic/game_main.h"
// is_testing sirve para testear cosas del juego a mano
Server::Server(const char* port, bool is_testing):
        srv(port), clients(), recv_queue(100), send_queues(), is_testing(is_testing) {}

void Server::run() {

    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    ReadInput read_input_t;
    read_input_t.start();


    std::vector<uint16_t> map = {
        0,0,0,0,0,0,0,
        0,0,0,2,0,0,0,
        0,0,5,5,5,5,0,
        0,0,0,5,5,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0};
    uint16_t fil = 6;
    uint16_t col = 7;
    SendMapMsg msg3(map, fil, col);
    int n = 1;

    while (read_input_t.is_alive()) {
        std::list<GenericMsg*> msgs;
        GenericMsg* msg;
        if (n == 1) {
            msgs.push_back(&msg3);
            send_queues.broadcast(msgs);
            break;
        }
        while (recv_queue.try_pop(msg)) {
            
        }
        send_queues.broadcast(msgs);
    }
    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}
