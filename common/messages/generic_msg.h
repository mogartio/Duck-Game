#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>

class SendProtocol;

class GenericMsg {
protected:
    enum typeMsg : uint8_t {
        RESPONSE_SERVER = 0x00,
        CUSTOMIZED_INFO = 0x01,
        LOBBY_MESSAGE = 0x02,
        GAME_MESSAGE = 0x03,
    };

private:
    typeMsg first_header;

protected:
    GenericMsg(typeMsg first_header);

public:
    virtual void accept_send(SendProtocol& visitor) = 0;
    // virtual GenericMsg accept_recv(Protocol& protocol);
    virtual uint8_t get_second_header() const;

    uint8_t get_first_header() const;

    virtual ~GenericMsg() = default;
};

class ResponseServerMsg: public GenericMsg {
protected:
    enum responseType : uint8_t {
        // HAY QUE CAMBIAR ESTO
        OK = 0x00,
        ERROR = 0x01,
    };

private:
    responseType second_header;

public:
    ResponseServerMsg(responseType second_header);

    virtual uint8_t get_second_header() const override;
};

class CustomizedMsg: public GenericMsg {
protected:
    enum customizedType : uint8_t {
        // HAY QUE CAMBIAR ESTO
        PLAYER_INFO = 0x00,
        MAP_INFO = 0x01,
        FINISH_GAME = 0x02,
        WINNER = 0x03,
    };

private:
    customizedType second_header;

public:
    CustomizedMsg(customizedType second_header);

    virtual uint8_t get_second_header() const override;
};

class LobbyMsg: public GenericMsg {
protected:
    enum lobbyType : uint8_t {
        // HAY QUE CAMBIAR ESTO
        EXAMPLE = 0x00,
        LOBBY_LIST = 0x01,
        JOINED_LOBBY = 0x02,
        SERVER_ERROR = 0x03,
        VIEW_LOBBIES = 0x04,
        CHOOSE_LOBBY = 0x05,
        CREATE_LOBBY = 0x06,
        START_GAME = 0x07,
        GO_BACK = 0x08,
    };

private:
    lobbyType second_header;

public:
    LobbyMsg(lobbyType second_header);

    virtual uint8_t get_second_header() const override;
};

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
    GameMsg(gameType second_header);

    virtual uint8_t get_second_header() const override;
};

#endif
