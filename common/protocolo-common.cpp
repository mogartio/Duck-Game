#include "protocolo-common.h"

#include <arpa/inet.h>

ProtocoloCommon::ProtocoloCommon(Socket& socket): socket(socket), was_closed(false) {}

void ProtocoloCommon::chk_closed_andif_fail(const char error_ms[]) const {
    if (was_closed) {
        throw SocketClosedError(error_ms);
    }
}

void ProtocoloCommon::send_u_int8_t(u_int8_t& data) {
    socket.sendall(&data, sizeof(u_int8_t), &was_closed);
    chk_closed_andif_fail("send u_int8_t");
}

u_int8_t ProtocoloCommon::recv_u_int8_t() {
    u_int8_t data;
    socket.recvall(&data, sizeof(u_int8_t), &was_closed);
    chk_closed_andif_fail("recv u_int8_t");
    return data;
}

void ProtocoloCommon::send_u_int16_t(u_int16_t& data) {
    u_int16_t data_net = htons(data);
    socket.sendall(&data_net, sizeof(u_int16_t), &was_closed);
    chk_closed_andif_fail("send u_int16_t");
}

u_int16_t ProtocoloCommon::recv_u_int16_t() {
    u_int16_t data_net;
    socket.recvall(&data_net, sizeof(u_int16_t), &was_closed);
    chk_closed_andif_fail("recv u_int16_t");
    return ntohs(data_net);
}

void ProtocoloCommon::send_string(std::string& data) {
    socket.sendall(data.data(), data.size(), &was_closed);
    chk_closed_andif_fail("send string");
}

std::string ProtocoloCommon::recv_string(u_int16_t& size) {
    std::string data(size, 0);
    socket.recvall(data.data(), size, &was_closed);
    chk_closed_andif_fail("recv string");
    data.resize(size);
    return data;
}
