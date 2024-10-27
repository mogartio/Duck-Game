#ifndef GENERIC_MSG_GAME_H
#define GENERIC_MSG_GAME_H

#include "generic_msg.h"

class GameMsg: public GenericMsg {
protected:
    enum gameType : uint8_t {
        // HAY QUE CAMBIAR ESTO
        PLAYER_INFO = 0x00,
        FINISH_GAME = 0x01,
        WINNER = 0x02,
        PICKUP_DROP_ITEM = 0x03,
        START_MOVE_LEFT = 0x04,
        STOP_MOVE_LEFT = 0x05,
        START_MOVE_RIGHT = 0x06,
        STOP_MOVE_RIGHT = 0x07,
        JUMP = 0x08,
        PLAY_DEAD = 0x09,
        SHOOT = 0x0A,
    };

private:
    gameType second_header;

public:
    explicit GameMsg(gameType second_header);

    virtual uint8_t get_second_header() const override;
};

class PickupDropItemMsg: public GameMsg {
public:
    PickupDropItemMsg();
    virtual void accept_send(Handler& protocol) override;
};

class StartMoveLeftMsg: public GameMsg {
public:
    StartMoveLeftMsg();
    virtual void accept_send(Handler& protocol) override;
};

class StopMoveLeftMsg: public GameMsg {
public:
    StopMoveLeftMsg();
    virtual void accept_send(Handler& protocol) override;
};

class StartMoveRightMsg: public GameMsg {
public:
    StartMoveRightMsg();
    virtual void accept_send(Handler& protocol) override;
};

class StopMoveRightMsg: public GameMsg {
public:
    StopMoveRightMsg();
    virtual void accept_send(Handler& protocol) override;
};

class JumpMsg: public GameMsg {
public:
    JumpMsg();
    virtual void accept_send(Handler& protocol) override;
};

class PlayDeadMsg: public GameMsg {
public:
    PlayDeadMsg();
    virtual void accept_send(Handler& protocol) override;
};

class ShootMsg: public GameMsg {
public:
    ShootMsg();
    virtual void accept_send(Handler& protocol) override;
};

class PlayerInfoMsg: public GameMsg {
public:
    PlayerInfoMsg();
    virtual void accept_send(Handler& protocol) override;
};

class FinishGameMsg: public GameMsg {
public:
    FinishGameMsg();
    virtual void accept_send(Handler& protocol) override;
};

class WinnerMsg: public GameMsg {
public:
    WinnerMsg();
    virtual void accept_send(Handler& protocol) override;
};
#endif  // CLIENT_GENERIC_MSG_H
