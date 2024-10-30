#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "client_protocol.h"

class Receiver: public Thread {
private:
    Queue<GenericMsg*>* recv_queue;
    ClientProtocol* protocol;

    void run() override;

public:
    explicit Receiver(Queue<GenericMsg*>* recv_queue, ClientProtocol* protocol);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();

};
#endif  // RECEIVER_H
