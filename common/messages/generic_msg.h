#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>

class SendProtocol;

class GenericMsg {
protected:
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

    virtual void accept_send(SendProtocol& visitor) = 0;

    virtual uint8_t get_second_header() const = 0;

    uint8_t get_first_header() const;

    virtual ~GenericMsg() = default;
};

#endif
