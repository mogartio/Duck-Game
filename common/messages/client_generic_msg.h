#ifndef CLIENT_MSG_H
#define CLIENT_MSG_H

#include "generic_msg.h"

class CustomizedPlayerInfoMsg: public CustomizedMsg {
public:
    CustomizedPlayerInfoMsg();

    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class ViewLobbiesMsg: public LobbyMsg {
public:
    ViewLobbiesMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class ChooseLobbyMsg: public LobbyMsg {
public:
    ChooseLobbyMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class CreateLobbyMsg: public LobbyMsg {
public:
    CreateLobbyMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class StartGameMsg: public LobbyMsg {
public:
    StartGameMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class GoBackMsg: public LobbyMsg {
public:
    GoBackMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class PickupDropItemMsg: public GameMsg {
public:
    PickupDropItemMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class StartMoveLeftMsg: public GameMsg {
public:
    StartMoveLeftMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class StopMoveLeftMsg: public GameMsg {
public:
    StopMoveLeftMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class StartMoveRightMsg: public GameMsg {
public:
    StartMoveRightMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class StopMoveRightMsg: public GameMsg {
public:
    StopMoveRightMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class JumpMsg: public GameMsg {
public:
    JumpMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class PlayDeadMsg: public GameMsg {
public:
    PlayDeadMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};

class ShootMsg: public GameMsg {
public:
    ShootMsg();
    virtual void accept_send(Send& protocol) override { protocol.sendClient(*this); }
};
#endif  // CLIENT_GENERIC_MSG_H
