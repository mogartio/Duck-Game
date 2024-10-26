#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>

#include "./../protocol/send.h"

class GenericMsg {
public:
    enum typeMsg : uint8_t {
        CUSTOMIZED_PLAYER_INFO = 0x01,

    };

private:
    typeMsg first_header;

protected:
    GenericMsg(uint8_t first_header);

public:
    virtual void accept_send(Send& protocol) = 0;
    virtual GenericMsg accept_recv(Send& protocol);
    virtual ~GenericMsg() = default;
};

#endif
