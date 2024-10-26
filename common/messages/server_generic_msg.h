#ifndef SERVER_MSG_H
#define SERVER_MSG_H

#include <string>

#include "generic_msg.h"

class ExampleMsg: public LobbyMsg {
private:
    std::string data;

public:
    ExampleMsg(std::string& data);

    std::string getData() const;

    virtual void accept_send(SendProtocol& protocol) override;
};

class LobbyListMsg: public LobbyMsg {
public:
    LobbyListMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class JoinedLobbyMsg: public LobbyMsg {
public:
    JoinedLobbyMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class ServerErrorMsg: public ResponseServerMsg {
public:
    ServerErrorMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class MapInfoMsg: public CustomizedMsg {
public:
    MapInfoMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class PlayerInfoMsg: public GameMsg {
public:
    PlayerInfoMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class FinishGameMsg: public GameMsg {
public:
    FinishGameMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class WinnerMsg: public GameMsg {
public:
    WinnerMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};
#endif  // SERVER_GENERIC_MSG_H
