#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Handler;

class GenericMsg {
public:

    enum MsgTypeHeader : uint8_t {
        CUSTOMIZED_PLAYER_INFO_MSG = 0,
        VIEW_LOBBIES_MSG,
        CHOOSE_LOBBY_MSG,
        CREATE_LOBBY_MSG,
        GO_BACK_MSG,
        EXIT_FROM_LOBBY_MSG,
        START_GAME_MSG,
        PICKUP_DROP_MSG,
        MOVE_LEFT_MSG,
        MOVE_RIGHT_MSG,
        JUMP_MSG,
        PLAY_DEAD_MSG,
        SHOOT_MSG,
        SEND_LOBBIES_LIST_MSG,
        EVERYTHING_OK_MSG,
        ERROR_MSG,
        SEND_MAP_MSG,
        GAME_ENDED_MSG,
        WINNER_MSG
    };

private:
    MsgTypeHeader header;

public:
    explicit GenericMsg();

    virtual void accept_send(Handler& handler) = 0;
    virtual void accept_recv(Handler& handler) = 0;
    uint8_t get_header() const;

    virtual ~GenericMsg() = default;
};
#endif
