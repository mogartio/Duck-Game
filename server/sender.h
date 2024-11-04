#ifndef SENDER_SERVER_H
#define SENDER_SERVER_H

#include "../common/sender.h"

#include "server_protocol.h"

class SenderServer: public Sender {
protected:
    virtual void assingProtocol() override { protocol = new ServerProtocol(skt); }

public:
    SenderServer(Queue<GenericMsg*>* send_queue, Socket& skt): Sender(send_queue, skt) {}
};
#endif  // SENDER_H
