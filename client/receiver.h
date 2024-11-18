#ifndef RECEIVER_CLIENT_H
#define RECEIVER_CLIENT_H

#include "../common/receiver.h"

class ReceiverClient: public Receiver {
protected:
    virtual void executeMsg(std::shared_ptr<GenericMsg> msg) override;

public:
    explicit ReceiverClient(Queue<std::shared_ptr<GenericMsg>>* recv_queue, ProtocoloCommon* protocol);
};
#endif  // RECEIVER_H
