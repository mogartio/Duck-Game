#ifndef RECIVER_H
#define RECIVER_H

#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/thread.h"

class Reciver: public Thread {
private:
    Socket& skt;

    Queue<std::string>& queue;

    std::atomic<bool> is_dead;

    void run() override;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del Reciver con el socket y la cola de mensajes
     */
    explicit Reciver(Socket& skt, Queue<std::string>& queue): 
                        skt(skt), queue(queue), is_dead(false) {}

    // ------------------- Metodos -------------------

    void close();

    
    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Reciver(const Reciver&) = delete;
    Reciver& operator=(const Reciver&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Reciver(Reciver&&) = delete;
    Reciver& operator=(Reciver&&) = delete;

    ~Reciver() = default;
};
#endif
