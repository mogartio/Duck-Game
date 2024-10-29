#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "protocolo-common.h"

class Sender: public Thread {
private:
    Queue<GenericMsg*>* send_queue;  // tiene que ser un puntero para poder cambiar la referencia
    ProtocoloCommon* protocol;

    void run() override;

public:
    Sender(Queue<GenericMsg*>* send_queue, ProtocoloCommon* protocol);

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
    void update_protocol(ProtocoloCommon* protocol);
};
#endif  // SENDER_H
