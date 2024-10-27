#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../common/messages/handler.h"
#include "../common/protocolo-common.h"

class Protocol: public ProtocoloCommon, public Handler {
public:
    explicit Protocol(Socket& socket): ProtocoloCommon(socket) {}

    void send(GenericMsg& msg) { msg.accept_send(*this); }

    using Handler::handle_recv;
    using Handler::handle_send;
    /*
    void handle_send(ServerExampleMsg1& msg) override {
        // mando header
        uint8_t header = msg.get_header();
        send_uint8_t(header);
        // mando longitud del string
        uint16_t dataSize = msg.get_data().size();
        send_uint16_t(dataSize);
        // mando string
        auto data = msg.get_data();
        send_string(data);
        return;
    }
    */
    /*
    GenericMsg* receive() override {
        uint8_t header = recv_uint8_t(); // recibo el header que representa al mensaje
        GenericMsg* msg = generate_msg(header); // genero el mensaje dado el header
        msg->accept_recv(*this);
        return msg;
    }
    void handle_recv(ClientExampleMsg1& msg) override {
        uint16_t dataSize = recv_uint16_t();
        std::string data = recv_string(dataSize);
        msg.set_data(data);
    }

    void handle_recv(ClientExampleMsg2& msg) override {
        uint8_t data = recv_uint8_t();
        msg.set_data(data);
    }

    GenericMsg* generate_msg(uint8_t header) {
        // pongo todos los case pero solo estaria recibiendo dos tipos de mensaje
        switch (header) {
            case GenericMsg::SERVER_EXAMPLE_MSG1_H:
                return new ServerExampleMsg1("");
            case GenericMsg::CLIENT_EXAMPLE_MSG1_H:
                return new ClientExampleMsg1("");
            case GenericMsg::CLIENT_EXAMPLE_MSG2_H:
                return new ClientExampleMsg2(0);
            default:
                return nullptr;
        }
    }
    */
};
#endif
