#include "server.h"

Server::Server(const std::string& port): skt_server(port.c_str()) {}

int Server::run() {
    try {
        // Creamos un aceptador que aceptará a los clientes
        // a través del socket `skt`.
        Aceptador aceptador_de_clientes(skt_server);
        // Iniciamos el aceptador para que acepte a los clientes
        aceptador_de_clientes.start();
        // Esperamos a que el usuario quiera salir
        std::string exit_comand;
        while (true) {
            std::cin >> exit_comand;  // esta accion es bloqueante
            if (exit_comand == "q") {
                skt_server.shutdown(2);  // cerramos la comunicacion del socket completamente para
                                         // que el aceptador termine
                skt_server.close();      // cerramos el socket
                break;
            }
        }
        // Esperamos a que el aceptador termine
        aceptador_de_clientes.join();
    } catch (...) {
        // Error desconocido
        std::cerr << "Error desconocido en el server" << std::endl;
        return -1;
    }
    return 0;
}
