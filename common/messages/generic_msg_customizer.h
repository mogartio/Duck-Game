#ifndef GENERIC_MSG_CUSTOMIZER_H
#define GENERIC_MSG_CUSTOMIZER_H

#include <string>

#include "generic_msg.h"

class CustomizedMsg: public GenericMsg {
protected:
    enum customizedType : uint8_t {
        CUSTOMIZER_PLAYER = 0x01,
        SELECT_MAP = 0x02,
        EDIT_MAP = 0x03,
        CREATE_NEW_MAP = 0x04,
        // HAY QUE CONTINUARLO Y MEJORARLO
    };

private:
    customizedType second_header;

public:
    explicit CustomizedMsg(customizedType second_header);

    virtual uint8_t get_second_header() const override;
};

class CustomizedPlayerInfoMsg: public CustomizedMsg {
public:
    CustomizedPlayerInfoMsg();

    virtual void accept_send(SendProtocol& protocol) override;
};

class MapInfoMsg: public CustomizedMsg {
public:
    MapInfoMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};
#endif  // GENERIC_MSG_LOBBYS_H
