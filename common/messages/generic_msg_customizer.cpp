#include "generic_msg_customizer.h"

#include "./../protocol/send.h"

CustomizedMsg::CustomizedMsg(customizedType second_header):
        GenericMsg(CUSTOMIZED_INFO), second_header(second_header) {}

uint8_t CustomizedMsg::get_second_header() const { return second_header; }

CustomizedPlayerInfoMsg::CustomizedPlayerInfoMsg(): CustomizedMsg(CUSTOMIZER_PLAYER) {}

void CustomizedPlayerInfoMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

MapInfoMsg::MapInfoMsg(): CustomizedMsg(EDIT_MAP) {}

void MapInfoMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }
