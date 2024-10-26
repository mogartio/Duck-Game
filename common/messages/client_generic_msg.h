#ifndef CLIENT_MSG_H
#define CLIENT_MSG_H

#include "generic_msg.h"

class CustomizedPlayerInfoMsg: public CustomizedMsg {
public:
    CustomizedPlayerInfoMsg();

    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ViewLobbiesMsg: public LobbyMsg {
public:
    ViewLobbiesMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ChooseLobbyMsg: public LobbyMsg {
public:
    ChooseLobbyMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class CreateLobbyMsg: public LobbyMsg {
public:
    CreateLobbyMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartGameMsg: public LobbyMsg {
public:
    StartGameMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class GoBackMsg: public LobbyMsg {
public:
    GoBackMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class PickupDropItemMsg: public GameMsg {
public:
    PickupDropItemMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartMoveLeftMsg: public GameMsg {
public:
    StartMoveLeftMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StopMoveLeftMsg: public GameMsg {
public:
    StopMoveLeftMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartMoveRightMsg: public GameMsg {
public:
    StartMoveRightMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StopMoveRightMsg: public GameMsg {
public:
    StopMoveRightMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class JumpMsg: public GameMsg {
public:
    JumpMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class PlayDeadMsg: public GameMsg {
public:
    PlayDeadMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ShootMsg: public GameMsg {
public:
    ShootMsg();
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};
#endif  // CLIENT_GENERIC_MSG_H
