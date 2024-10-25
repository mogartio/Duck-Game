#ifndef LOBBY_MANAGER_PROTOCOL_H
#define LOBBY_MANAGER_PROTOCOL_H

#include "../common/messages/server_handler.h"
#include "../common/messages/server_generic_msg.h"
#include "../common/protocol.h"

class LobbyManagerProtocol : public Protocol<ServerHandler>, public ServerHandler {
public:
    explicit LobbyManagerProtocol(Socket& skt) : Protocol(skt) {}

    void send(GenericMsg<ServerHandler>* msg) override {
        msg->accept(*this);
    }

    GenericMsg<ServerHandler>* receive() override {
        // GenericMsg<ServerHandler>* msg = recv_queue.pop();
        // msg->acceptReceiver(*this);
        return nullptr;
    }

    void handle(ExampleMsg& msg) override {
        std::cout << msg.getData() << std::endl;
        return;
    }

};

#endif 
