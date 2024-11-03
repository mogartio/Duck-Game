#include "server.h"

#include <list>
#include <utility>

#include "game_logic/game_main.h"
// is_testing sirve para testear cosas del juego a mano
Server::Server(const char* port, bool is_testing):
        srv(port), clients(), recv_queue(100), send_queues(), is_testing(is_testing) {}

void Server::run() {
    GameMain game(recv_queue, "juancito", "juancito", is_testing, send_queues);
    game.start();
    // pongo a correr el acceptor
    Acceptor acceptor(std::move(srv), clients, recv_queue, send_queues);
    acceptor.start();
    ReadInput read_input_t;
    // read_input_t.start();
    // read_input_t.start();

    WinnerMsg msg1("juancito");

    UpdatedPlayerInfoMsg msg2("juancito", std::make_pair(4, 3), 0, 1);

    std::vector<uint16_t> map = {5,5,5,0,0,2,0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint16_t fil = 6;
    uint16_t col = 7;
    SendMapMsg msg3(map, fil, col);


    while (read_input_t.is_alive()) {
        std::list<GenericMsg*> msgs;
        GenericMsg* msg;
        while (recv_queue.try_pop(msg)) {
            std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2)
                      << std::setfill('0') << static_cast<int>(msg->get_header()) << std::endl;
            msgs.push_back(&msg1);
            msgs.push_back(&msg2);
        }
        send_queues.broadcast(msgs);
    }
    acceptor.stop();
    acceptor.join();
    read_input_t.join();
}
