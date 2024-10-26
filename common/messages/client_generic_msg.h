#ifndef CLIENT_MSG_H
#define CLIENT_MSG_H

#include "generic_msg.h"

class CustomizedPlayerInfoMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ViewLobbiesMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ChooseLobbyMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class CreateLobbyMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartGameMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class GoBackMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class PickupDropItemMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartMoveLeftMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StopMoveLeftMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StartMoveRightMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class StopMoveRightMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class JumpMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class PlayDeadMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};

class ShootMsg: public GenericMsg {
    virtual void accept_send(Send& protocol) override { protocol.send(*this); }
};
#endif  // CLIENT_GENERIC_MSG_H
