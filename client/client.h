#ifndef CLIENT_H
#define CLIENT_H

#include "../common/socket.h"

#include <string>

class Client {
private:
    Socket skt_client;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del cliente
     */
    explicit Client(const std::string& hostname, const std::string& port): 
                                skt_client(hostname.c_str(), port.c_str()) {}

    // ------------------- Metodos -------------------
    /*
     * El metodo run se encarga de correr el juego
     */
    int run();

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    ~Client() = default;
};
#endif
