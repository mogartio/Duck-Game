#ifndef PROTOCOL_SOCKET_H
#define PROTOCOL_SOCKET_H

#include <cstdint>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "./../socket/socket.h"
#include "./../socket/socket_error.h"

class ProtocolSocket {
protected:
    bool was_closed;

private:
    Socket& skt;

    /*
     * Lanza SocketError en caso de que el socket se haya cerrado al enviar o recibir datos.
     */
    void chk_closed_andif_fail(const char error_ms[]) const;

protected:
    /*
     * Envia un uint8_t a través del socket.
     */
    void send_uint8_t(uint8_t& data);

    /*
     * Recibe un uint8_t a través del socket.
     */
    uint8_t recv_uint8_t();

    /*
     * Envia un uint16_t a través del socket.
     */
    void send_uint16_t(uint16_t& data);

    /*
     * Recibe un uint16_t a través del socket.
     */
    uint16_t recv_uint16_t();

    /*
     * Envia un string a través del socket.
     */
    void send_string(std::string& data);

    /*
     * Recibe un string a través del socket.
     */
    std::string recv_string(uint16_t& msg_size);

public:
    /*
     * Constructor de la clase Protocolo.
     */
    ProtocolSocket(Socket& skt);

    /*
     * Se deshabilita la copia y operador asignacion por copia
     */
    ProtocolSocket(const ProtocolSocket&) = delete;
    ProtocolSocket& operator=(const ProtocolSocket&) = delete;

    /*
     * Destructor de la clase Protocolo.
     */
    ~ProtocolSocket() = default;
};
#endif
