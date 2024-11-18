#ifndef SENDER_SERVER_H
#define SENDER_SERVER_H
#include <memory>
#include <string>

#include "../common/sender.h"

class Client;

class SenderServer: public Sender {
protected:
    Client* client;

    void execute(std::shared_ptr<GenericMsg> msg) override;

public:
    SenderServer(Queue<std::shared_ptr<GenericMsg>>* send_queue, ProtocoloCommon* protocol,
                 Client* client);
};
#endif  // SENDER_H
