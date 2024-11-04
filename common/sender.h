#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "protocolo-common.h"

class Sender: public Thread {
protected:
    Queue<GenericMsg*>* send_queue;  // tiene que ser un puntero para poder cambiar la referencia
    Socket& skt;
    ProtocoloCommon* protocol;

    void run() override;

    virtual void assingProtocol() = 0;

public:
    Sender(Queue<GenericMsg*>* send_queue, Socket& skt);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();
};
#endif  // SENDER_H
