#ifndef CLIENT_MSG_H
#define CLIENT_MSG_H

#include "generic_msg.h"

class CustomizedPlayerInfoMsg: public CustomizedMsg {
public:
    CustomizedPlayerInfoMsg();

    virtual void accept_send(SendProtocol& protocol) override;
};

class ViewLobbiesMsg: public LobbyMsg {
public:
    ViewLobbiesMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class ChooseLobbyMsg: public LobbyMsg {
public:
    ChooseLobbyMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class CreateLobbyMsg: public LobbyMsg {
public:
    CreateLobbyMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StartGameMsg: public LobbyMsg {
public:
    StartGameMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class GoBackMsg: public LobbyMsg {
public:
    GoBackMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class PickupDropItemMsg: public GameMsg {
public:
    PickupDropItemMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StartMoveLeftMsg: public GameMsg {
public:
    StartMoveLeftMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StopMoveLeftMsg: public GameMsg {
public:
    StopMoveLeftMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StartMoveRightMsg: public GameMsg {
public:
    StartMoveRightMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StopMoveRightMsg: public GameMsg {
public:
    StopMoveRightMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class JumpMsg: public GameMsg {
public:
    JumpMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class PlayDeadMsg: public GameMsg {
public:
    PlayDeadMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class ShootMsg: public GameMsg {
public:
    ShootMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};
#endif  // CLIENT_GENERIC_MSG_H
