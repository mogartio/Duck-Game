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

    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class LobbyListMsg: public LobbyMsg {
public:
    LobbyListMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class JoinedLobbyMsg: public LobbyMsg {
public:
    JoinedLobbyMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class ServerErrorMsg: public ResponseServerMsg {
public:
    ServerErrorMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class MapInfoMsg: public CustomizedMsg {
public:
    MapInfoMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class PlayerInfoMsg: public GameMsg {
public:
    PlayerInfoMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class FinishGameMsg: public GameMsg {
public:
    FinishGameMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};

class WinnerMsg: public GameMsg {
public:
    WinnerMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendServer(*this); }
};
#endif  // SERVER_GENERIC_MSG_H
