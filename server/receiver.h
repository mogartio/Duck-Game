#ifndef RECEIVER_SERVER_H
#define RECEIVER_SERVER_H

#include "../common/receiver.h"

class Client;

class ReceiverServer: public Receiver {
private:
    Client* client;

protected:
    virtual void executeMsg(GenericMsg* msg) override;

public:
    explicit ReceiverServer(Queue<GenericMsg*>* recv_queue_game, ProtocoloCommon* protocol,
                            Client* client);
    // void switch_q(Queue<GenericMsg*>* q);
};
#endif  // RECEIVER_H
