#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "queue.h"
#include "socket/socket.h"
#include "thread.h"

#include "protocol.h"

class Receiver: public Thread {
private:
    Queue<std::string>* recv_queue;
    Protocol* protocol;

    void run() override;

public:
    explicit Receiver(Queue<std::string>* recv_queue, Protocol* protocol);
    
    /* 
    * Detiene la ejecución del hilo seteando _keep_running en false.
    */
    void kill();

    /*
    * Actualiza la referencia a la cola de recepción.
    */
    void update_recv_queue(Queue<std::string>* recv_queue);

    /* 
    * Actualiza la referencia al protocolo.
    */
    void update_protocol(Protocol* protocol);
};
#endif  // RECEIVER_H
