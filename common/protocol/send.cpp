#include "send.h"

void SendServer::send(const ExampleMsg& msg) {
    uint8_t first_header = GenericMsg::CUSTOMIZED_PLAYER_INFO;
    send_uint8_t(first_header);
    std::string data = msg.getData();
    send_string(data);
}
