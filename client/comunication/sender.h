#ifndef SENDER_H
#define SENDER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/queue.h"
#include "../common/queuesStructs/clientInfo.cpp"

class Sender: public Thread {
private:
    Socket& skt;

    Queue<ClientInfo*>& queue;

    std::atomic<bool> is_dead;

    void run() override;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del receiver con el socket y la cola de mensajes
     */
    explicit Sender(Socket& skt, Queue<ClientInfo*>& queue): 
                    skt(skt), queue(queue), is_dead(false) {}

    // ------------------- Metodos -------------------

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
