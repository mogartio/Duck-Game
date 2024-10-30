#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// Aca se puede directamente agregar los imports de los handlers
// No se porque se los declara tempranamente aca????
class HandlerSender;
class HandlerReceiver;
// class HandlerReader;

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
        START_ACTION_MSG = 0x08,
        STOP_ACTION_MSG = 0x09,
        SEND_LOBBIES_LIST_MSG = 0x0A,
        EVERYTHING_OK_MSG = 0x0B,
        ERROR_MSG = 0x0C,
        SEND_MAP_MSG = 0x0D,
        GAME_ENDED_MSG = 0x0E,
        WINNER_MSG = 0x0F,
        UPDATED_PLAYER_INFO_MSG = 0x10,
        PROJECTILE_INFO_MSG = 0x11,
    };

    enum ActionId : uint8_t {
        MOVE_LEFT = 0x01,
        MOVE_RIGHT = 0x02,
        JUMP = 0x03,
        SHOOT = 0x04,
        PLAY_DEAD = 0x05,
    };

    enum FacingDirection : uint8_t {
        RIGHT = 0x01,
        LEFT = 0x03,
    };

private:
    MsgTypeHeader header;

public:
    GenericMsg() {}

    virtual void accept_send(HandlerSender& handler) = 0;
    virtual void accept_recv(HandlerReceiver& handler) = 0;
    // virtual void accept_read(HandlerReceiver& handler) = 0;
    uint8_t get_header() const { return header; }
    virtual ~GenericMsg() = default;
};


#endif
