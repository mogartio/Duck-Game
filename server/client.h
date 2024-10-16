#ifndef CLIENT_H
#define CLIENT_H

#include <utility>

#include "receiver.h"
#include "sender.h"


class Client {
private:
    Socket socket;

    std::atomic<bool> is_dead;

    Receiver receiver;

    Sender sender;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del cliente con el socket y la cola de mensajes
     */
    explicit Client(Socket&& skt,Queue<std::string>& receiver_queue, const u_int& id_client);

    // ------------------- Metodos -------------------

    /*
     * Metodo que cierra el cliente y sus medios de comunicacion
     */
    void kill();

    /*
     * Metodo que verifica si el cliente esta muerto
     */
    bool isDead() const;

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

    // ------------------- Destructor -------------------
    /*
     * Destructor del cliente
     */
    ~Client() = default;
};
#endif
