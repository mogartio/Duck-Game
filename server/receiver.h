#ifndef RECEIVER_SERVER_H
#define RECEIVER_SERVER_H

#include "../common/receiver.h"

class Client;

class ReceiverServer: public Receiver {
private:
    Client* client;

protected:
    virtual void executeMsg(GenericMsg* msg) override;

    virtual void assingProtocol() override;

public:
    explicit ReceiverServer(Queue<GenericMsg*>* recv_queue_game, Client* client, Socket& skt);
};
#endif  // RECEIVER_H
