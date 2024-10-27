#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "server_protocol.h"

class Sender: public Thread {
private:
    Queue<GenericMsg*>* send_queue;  // tiene que ser un puntero para poder cambiar la referencia
    ServerProtocol* protocol;

    void run() override;

public:
    Sender(Queue<GenericMsg*>* send_queue, ServerProtocol* protocol);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();

    /*
     * Actualiza la referencia a la cola de envío.
     */
    void update_send_queue(Queue<GenericMsg*>* new_send_queue);


    /*
     * Actualiza la referencia al protocolo.
     */
    void update_protocol(ServerProtocol* protocol);
};
#endif  // SENDER_H
