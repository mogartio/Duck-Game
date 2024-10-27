#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common/messages/handler.h"
#include "../common/messages/generic_msg.h"
#include "../common/protocol.h"

class ClientProtocol : public Protocol, public Handler {
public:
    explicit ClientProtocol(Socket& skt): Protocol(skt) {}

    void send(GenericMsg* msg) override {
        msg->accept_send(*this);
    }

    GenericMsg* receive() override {
        uint8_t header = recv_uint8_t(); // recibo el header que representa al mensaje
        GenericMsg* msg = generate_msg(header); // genero el mensaje dado el header
        msg->accept_recv(*this);
        return msg;
    }

    using Handler::handle_send;
    using Handler::handle_recv;

    void handle_send(ClientExampleMsg1& msg) override {
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

    void handle_send(ClientExampleMsg2& msg) override {
        // mando header
        uint8_t header = msg.get_header();
        send_uint8_t(header);
        // mando data
        uint8_t data = msg.get_data();
        send_uint8_t(data);
        return;
    }

    void handle_recv(ServerExampleMsg1& msg) override {
        uint16_t dataSize = recv_uint16_t();
        std::string data = recv_string(dataSize);
        msg.set_data(data);
    }

    GenericMsg* generate_msg(uint8_t header) {
        // pongo todos los case pero solo estaria recibiendo un solo tipo de mensaje
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

};

#endif // CLIENT_PROTOCOL_H
