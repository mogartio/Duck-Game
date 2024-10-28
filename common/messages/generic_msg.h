#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class HandlerSender;
class HandlerReceiver;

class GenericMsg {
public:
    enum MsgTypeHeader : uint8_t {
        CUSTOMIZED_PLAYER_INFO_MSG = 0x01,
        VIEW_LOBBIES_MSG = 0x02,
        CHOOSE_LOBBY_MSG = 0x03,
        CREATE_LOBBY_MSG = 0x04,
        GO_BACK_MSG = 0x05,
        EXIT_FROM_LOBBY_MSG = 0x06,
        START_GAME_MSG = 0x07,
        PICKUP_DROP_MSG = 0x08,
        MOVE_LEFT_MSG = 0x09,
        MOVE_RIGHT_MSG = 0x0A,
        JUMP_MSG = 0x0B,
        PLAY_DEAD_MSG = 0x0C,
        SHOOT_MSG = 0x0D,
        SEND_LOBBIES_LIST_MSG = 0x0E,
        EVERYTHING_OK_MSG = 0x0F,
        ERROR_MSG = 0x10,
        SEND_MAP_MSG = 0x11,
        GAME_ENDED_MSG = 0x12,
        WINNER_MSG = 0x13,
    };

private:
    MsgTypeHeader header;

public:
    GenericMsg() {}

    virtual void accept_send(HandlerSender& handler) = 0;
    virtual void accept_recv(HandlerReceiver& handler) = 0;
    uint8_t get_header() const { return header; }
    virtual void print_info() const = 0;
    virtual ~GenericMsg() = default;
};


#endif
