#ifndef SERVER_H
#define SERVER_H
#include <string>

#include "aceptador.h"

class Server {
private:
    Socket skt_server;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor de la caja
     */
    explicit Server(const std::string& port);

    // ------------------- Metodos -------------------
    /*
     * El metodo run se encarga de correr el juego
     */
    int run();

    // ------------------- Restricciones -------------------

    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

    ~Server() = default;
};
#endif
