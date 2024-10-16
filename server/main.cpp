#include <iostream>

#include "server.h"

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "Bad number of arguments in server side\n";
        return -1;
    }
    /* Aca arranca el codigo del servidor */
    const std::string port = argv[1];

    // Creamos el servidor
    Server server(port);
    // Corremos el servidor
    return server.run();
}
