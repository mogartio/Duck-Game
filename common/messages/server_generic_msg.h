#ifndef SERVER_MSG_H
#define SERVER_MSG_H

#include <string>

#include "generic_msg.h"

class ExampleMsg: public GenericMsg {
private:
    std::string data;

public:
    // ExampleMsg(std::string data) : data(data) {}

    std::string getData() const;

    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class LobbyListMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class JoinedLobbyMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ServerErrorMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class MapInfoMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class PlayerInfoMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class FinishGameMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class WinnerMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};
#endif  // SERVER_GENERIC_MSG_H
