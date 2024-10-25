#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "../common/queue.h"
#include "../common/socket/socket.h"
#include "thread.h"

#include "../common/protocol.h"
#include "../common/messages/server_handler.h"

class Receiver: public Thread {
private:
    Queue<GenericMsg<ServerHandler>*>* recv_queue;
    Protocol<ServerHandler>* protocol;

    void run() override;

public:
    explicit Receiver(Queue<GenericMsg<ServerHandler>*>* recv_queue, Protocol<ServerHandler>* protocol);
    
    /* 
    * Detiene la ejecución del hilo seteando _keep_running en false.
    */
    void kill();

    /*
    * Actualiza la referencia a la cola de recepción.
    */
    void update_recv_queue(Queue<GenericMsg<ServerHandler>*>* recv_queue);

    /* 
    * Actualiza la referencia al protocolo.
    */
    void update_protocol(Protocol<ServerHandler>* protocol);
};
#endif  // RECEIVER_H
