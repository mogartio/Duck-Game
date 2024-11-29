#ifndef RECEIVER_SERVER_H
#define RECEIVER_SERVER_H

#include "../../common/receiver.h"

class Client;

class ReceiverServer: public Receiver {
private:
    Client* client;

protected:
    virtual void executeMsg(std::shared_ptr<GenericMsg> msg) override;

public:
    explicit ReceiverServer(Queue<std::shared_ptr<GenericMsg>>* recv_queue_game,
                            ProtocoloCommon* protocol, Client* client);
    void switch_q(Queue<std::shared_ptr<GenericMsg>>* q) { this->recv_queue = q; };
};
#endif  // RECEIVER_H
