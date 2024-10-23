#include "protocol.h"

Protocol::Protocol(Socket& skt): skt(skt), was_closed(false) {}

void Protocol::chk_closed_andif_fail(const char error_ms[]) const {
    if (was_closed) {
        throw SocketClosedError(error_ms);
    }
}

void Protocol::send_uint8_t(uint8_t& data) {
    skt.sendall(&data, sizeof(uint8_t), &was_closed);
    chk_closed_andif_fail("send uint8_t");
}

uint8_t Protocol::recv_uint8_t() {
    uint8_t data;
    skt.recvall(&data, sizeof(uint8_t), &was_closed);
    chk_closed_andif_fail("recv uint8_t");
    return data;
}

void Protocol::send_uint16_t(uint16_t& data) {
    uint16_t data_net = htons(data);
    skt.sendall(&data_net, sizeof(uint16_t), &was_closed);
    chk_closed_andif_fail("send uint16_t");
}

uint16_t Protocol::recv_uint16_t() {
    uint16_t data_net;
    skt.recvall(&data_net, sizeof(uint16_t), &was_closed);
    chk_closed_andif_fail("recv uint16_t");
    return ntohs(data_net);
}

void Protocol::send_string(std::string& data) {
    skt.sendall(data.data(), data.size(), &was_closed);
    chk_closed_andif_fail("send string");
}

std::string Protocol::recv_string(uint16_t& msg_size) {
    std::vector<char> msg(msg_size);
    skt.recvall(msg.data(), msg_size, &was_closed);
    chk_closed_andif_fail("recv string");
    return std::string(msg.data(), msg.size());
}
