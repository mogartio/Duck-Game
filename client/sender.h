#ifndef SENDER_CLIENT_H
#define SENDER_CLIENT_H

#include "../common/sender.h"

#include "client_protocol.h"

class SenderClient: public Sender {
protected:
    virtual void assingProtocol() override { protocol = new ClientProtocol(skt); }

public:
    SenderClient(Queue<GenericMsg*>* send_queue, Socket& skt): Sender(send_queue, skt) {}
};
#endif  // SENDER_H
