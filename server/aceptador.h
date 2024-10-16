#ifndef ACEPTADOR_H
#define ACEPTADOR_H


#include <list>

#include "./../common/socket.h"

#include "./../common/thread.h"

#include "client.h"


/*
 * Aca esta el TDA `Aceptador` que es el que se encarga de aceptar a los clientes
 * */
class Aceptador: public Thread {
private:
    Socket& skt;

    std::list<Client> clients;

    Queue<std::string> receiver_queue;

    /*
     * Metodo para aceptar a un solo cliente
     */
    void acceptClient(const u_int& id_client);

    /*
     * Metodo que va eliminando a los clientes que se desconectaron
     */
    void cleanClients();

    /*
     * Metodo que cierra todo
     */
    void killAllClients();

public:
    /*
     * Constructor del aceptador del servidor
     */
    explicit Aceptador(Socket& skt);


    /*
     * Implementamos el método `run` que se encarga de aceptar a los clientes
     * a través del socket.
     */
    void run() override;

    /*
     * Destructor del aceptador del servidor
     */
    ~Aceptador();

    // ------------------ Desabilitamos -----------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Aceptador(const Aceptador&) = delete;
    Aceptador& operator=(const Aceptador&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Aceptador(Aceptador&&) = delete;
    Aceptador& operator=(Aceptador&&) = delete;
};
#endif
