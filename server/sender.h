#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/protocol.h"
#include "../common/messages/server_handler.h"

class Sender: public Thread {
private:
    Queue<GenericMsg<ServerHandler>*>* send_queue; // tiene que ser un puntero para poder cambiar la referencia
    Protocol<ServerHandler>* protocol;

    void run() override;

public:
    Sender(Queue<GenericMsg<ServerHandler>*>* send_queue, Protocol<ServerHandler>* protocol);
    
    /* 
    * Detiene la ejecución del hilo seteando _keep_running en false.
    */
    void kill();

    /*
    * Actualiza la referencia a la cola de envío.
    */
    void update_send_queue(Queue<GenericMsg<ServerHandler>*>* new_send_queue);


    /*
    * Actualiza la referencia al protocolo.
    */
    void update_protocol(Protocol<ServerHandler>* protocol);

};
#endif  // SENDER_H
