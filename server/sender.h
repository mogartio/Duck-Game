#ifndef SENDER_H
#define SENDER_H

#include "./../common/socket.h"
#include "./../common/thread.h"
#include "./../common/queue.h"


class Sender: public Thread {
private:
    Socket& skt;

    Queue<std::string> queue;

    std::atomic<bool>& is_dead;

    const u_int id_client;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del receiver con el socket y la cola de mensajes
     */
    explicit Sender(Socket& skt, std::atomic<bool>& is_dead, const u_int& id_client);

    // ------------------- Metodos -------------------

    /*
     * Metodo que corre el hilo
     */
    void run() override;

    void close();

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;

    ~Sender() = default;
};
#endif