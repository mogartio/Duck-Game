#ifndef SERVER_GENERIC_MSG_H
#define SERVER_GENERIC_MSG_H

#include "generic_msg.h"
#include "server_handler.h"
#include <string>

class ExampleMsg : public GenericMsg<ServerHandler> {
    private: 
        std::string data;
    public: 
    ExampleMsg(std::string data) : data(data) {}
    
    void accept(ServerHandler& handler) override {
        handler.handle(*this);
    }
    
    std::string getData() {
        return data;
    }
};

// class LobbyListMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class JoinedLobbyMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class ServerErrorMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class MapInfoMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class PlayerInfoMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class FinishGameMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

// class WinnerMsg : public GenericMsg<ServerHandler> {
//     void accept(ServerHandler& handler) override {
//         handler.handle(*this);
//     }
// };

#endif // SERVER_GENERIC_MSG_H
