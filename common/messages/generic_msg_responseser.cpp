#include "generic_msg_responseser.h"

#include "./../protocol/send.h"

ResponseServerMsg::ResponseServerMsg(responseType second_header):
        GenericMsg(RESPONSE_SERVER), second_header(second_header) {}

uint8_t ResponseServerMsg::get_second_header() const { return second_header; }

EverythingOkey::EverythingOkey(): ResponseServerMsg(EVERYTHING_WENT_WELL) {}

void EverythingOkey::accept_send(SendProtocol& protocol) { protocol.send(*this); }

SomethingWrong::SomethingWrong(): ResponseServerMsg(SOMETHING_WAS_WRONG) {}

void SomethingWrong::accept_send(SendProtocol& protocol) { protocol.send(*this); }
