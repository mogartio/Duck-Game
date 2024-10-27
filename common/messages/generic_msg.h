#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Handler;

class GenericMsg {
public:
    const static uint8_t SERVER_EXAMPLE_MSG1_H = 0x01;
    const static uint8_t CLIENT_EXAMPLE_MSG1_H = 0x02;
    const static uint8_t CLIENT_EXAMPLE_MSG2_H = 0x03;

    enum typeMsg : uint8_t {
        RESPONSE_SERVER = 0x00,
        LOBBY_MESSAGE = 0x01,
        CUSTOMIZED_INFO = 0x02,
        GAME_MESSAGE = 0x03,
    };

private:
    typeMsg first_header;

public:
    explicit GenericMsg(typeMsg first_header);

    virtual void accept_send(Handler& handler) = 0;
    // virtual void accept_recv(Handler& handler) = 0;
    virtual uint8_t get_second_header() const = 0;
    uint8_t get_first_header() const;
    virtual ~GenericMsg() = default;
};
#endif
