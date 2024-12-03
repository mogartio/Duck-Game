#include "server.h"

#include <list>
#include <utility>

// is_testing sirve para testear cosas del juego a mano
Server::Server(const char* port, bool is_testing, bool is_cheating):
        port(port), is_testing(is_testing), is_cheating(is_cheating), _keep_running(true) {}

void Server::run() {
    // pongo a correr el acceptor
    Acceptor acceptor(port, is_testing, is_cheating);
    acceptor.start();

    while (_keep_running) {
        if (!is_testing && !is_cheating) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "q") {
                _keep_running = false;
            }
        }
    }

    acceptor.stop();
    acceptor.join();
}
