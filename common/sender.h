#ifndef SENDER_H
#define SENDER_H
#include <memory>
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"
#include "./../common/messages/generic_msg.h"

#include "protocolo-common.h"

class Sender: public Thread {
protected:
    Queue<std::shared_ptr<GenericMsg>>*
            send_queue;  // tiene que ser un puntero para poder cambiar la referencia
    ProtocoloCommon* protocol;

    void run() override;

    virtual void execute(std::shared_ptr<GenericMsg> msg);

public:
    Sender(Queue<std::shared_ptr<GenericMsg>>* send_queue, ProtocoloCommon* protocol);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();
};
#endif  // SENDER_H
