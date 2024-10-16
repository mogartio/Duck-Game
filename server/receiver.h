#ifndef RECEIVER_H
#define RECEIVER_H

#include "./../common/socket.h"
#include "./../common/queue.h"
#include "./../common/thread.h"

class Receiver: public Thread {
private:
    Socket& skt;

    Queue<std::string>& receiver_queue;

    std::atomic<bool>& is_dead;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del receiver con el socket y la cola de mensajes
     */
    explicit Receiver(Socket& skt, Queue<std::string>& receiver_queue, std::atomic<bool>& is_dead);

    // ------------------- Metodos -------------------

    /*
     * Metodo que corre el hilo
     */
    void run() override;

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Receiver(Receiver&&) = delete;
    Receiver& operator=(Receiver&&) = delete;

    ~Receiver() = default;
};
#endif
