#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "protocolo-common.h"

class Receiver: public Thread {
private:
    Queue<GenericMsg*>* recv_queue;
    ProtocoloCommon* protocol;

    void run() override;

public:
    explicit Receiver(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();

    /*
     * Actualiza la referencia a la cola de recepción.
     */
    void update_recv_queue(Queue<GenericMsg*>* recv_queue);

    /*
     * Actualiza la referencia al protocolo.
     */
    void update_protocol(ProtocoloCommon* protocol);
};
#endif  // RECEIVER_H
