#ifndef RECEIVER_CLIENT_H
#define RECEIVER_CLIENT_H

#include "../common/receiver.h"

class ReceiverClient: public Receiver {
protected:
    virtual void executeMsg(GenericMsg* msg) override;

public:
    explicit ReceiverClient(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol);
};
#endif  // RECEIVER_H
