#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "protocolo-common.h"

class Receiver: public Thread {
protected:
    Queue<GenericMsg*>* recv_queue;
    ProtocoloCommon* protocol;

    void run() override;

    virtual void executeMsg(GenericMsg* msg) = 0;

public:
    explicit Receiver(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();
};
#endif  // RECEIVER_H
