#include "generic_msg.h"

GenericMsg::GenericMsg(typeMsg first_header): first_header(first_header) {}

uint8_t GenericMsg::get_first_header() const { return first_header; }
