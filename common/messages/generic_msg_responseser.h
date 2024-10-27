#ifndef GENERIC_MSG_RESPONSESER_H
#define GENERIC_MSG_RESPONSESER_H

#include <string>

#include "generic_msg.h"

class ResponseServerMsg: public GenericMsg {
protected:
    enum responseType : uint8_t {
        EVERYTHING_WENT_WELL = 0x01,
        SOMETHING_WAS_WRONG = 0x02,
    };

private:
    responseType second_header;

public:
    explicit ResponseServerMsg(responseType second_header);

    virtual uint8_t get_second_header() const override;
};

class EverythingOkey: public ResponseServerMsg {
public:
    EverythingOkey();
    virtual void accept_send(Handler& protocol) override;
};

class SomethingWrong: public ResponseServerMsg {
public:
    SomethingWrong();
    virtual void accept_send(Handler& protocol) override;
};

#endif  // GENERIC_MSG_LOBBYS_H
