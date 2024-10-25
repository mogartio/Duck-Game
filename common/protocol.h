#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket/socket.h"
#include "socket/socket_error.h"
#include "messages/generic_msg.h"
#include <cstdint>
#include <string>
#include <arpa/inet.h>
#include <vector>

template <typename HandlerType>
class Protocol {
private:
    Socket& skt;

    /*
     * Lanza SocketError en caso de que el socket se haya cerrado al enviar o recibir datos.
     */
    void chk_closed_andif_fail(const char error_ms[]) const {
        if (was_closed) {
            throw SocketClosedError(error_ms);
        }
    }

public:
    bool was_closed;
    /*
     * Envia un uint8_t a través del socket.
     */
    void send_uint8_t(uint8_t& data) {
        skt.sendall(&data, sizeof(uint8_t), &was_closed);
        chk_closed_andif_fail("send uint8_t");
    }

    /*
     * Recibe un uint8_t a través del socket.
     */
    uint8_t recv_uint8_t() {
        uint8_t data;
        skt.recvall(&data, sizeof(uint8_t), &was_closed);
        chk_closed_andif_fail("recv uint8_t");
        return data;
    }

    /*
     * Envia un uint16_t a través del socket.
     */
    void send_uint16_t(uint16_t& data) {
        uint16_t data_net = htons(data);
        skt.sendall(&data_net, sizeof(uint16_t), &was_closed);
        chk_closed_andif_fail("send uint16_t");
    }

    /*
     * Recibe un uint16_t a través del socket.
     */
    uint16_t recv_uint16_t() {
        uint16_t data_net;
        skt.recvall(&data_net, sizeof(uint16_t), &was_closed);
        chk_closed_andif_fail("recv uint16_t");
        return ntohs(data_net);
    }
    /*
     * Envia un string a través del socket.
     */
    void send_string(std::string& data) {
        skt.sendall(data.data(), data.size(), &was_closed);
        chk_closed_andif_fail("send string");
    }
    /*
     * Recibe un string a través del socket.
     */
    std::string recv_string(uint16_t& msg_size) {
        std::vector<char> msg(msg_size);
        skt.recvall(msg.data(), msg_size, &was_closed);
        chk_closed_andif_fail("recv string");
        return std::string(msg.data(), msg.size());
    }

    /*
    * Constructor de la clase Protocolo.
    */
    Protocol(Socket& skt): skt(skt), was_closed(false) {}


    /*
    * Se deshabilita la copia y operador asignacion por copia 
    */
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    /*
    * Metodos virtuales puros de la clase Protocolo.
    */
   virtual void send(GenericMsg<HandlerType>* data) = 0;
   virtual GenericMsg<HandlerType>* receive() = 0;

    /*
    * Destructor de la clase Protocolo.
    */
    virtual ~Protocol() = default;
};

#endif 
