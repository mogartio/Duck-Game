#ifndef RECEIVER_CLIENT_H
#define RECEIVER_CLIENT_H

#include "../common/receiver.h"

#include "client_protocol.h"

class ReceiverClient: public Receiver {
protected:
    virtual void executeMsg(GenericMsg* msg) override;

    virtual void assingProtocol() override;

public:
    explicit ReceiverClient(Queue<GenericMsg*>* recv_queue, Socket& skt);
};
#endif  // RECEIVER_H
