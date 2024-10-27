#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket/socket.h"
#include "socket/socket_error.h"
#include "messages/generic_msg.h"
#include <cstdint>
#include <string>
#include <arpa/inet.h>
#include <vector>

class Protocol {
private:
    Socket& skt;

    /*
     * Lanza SocketError en caso de que el socket se haya cerrado al enviar o recibir datos.
     */
    void chk_closed_andif_fail(const char error_ms[]) const;

public:
    bool was_closed;
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

    /*
    * Constructor de la clase Protocolo.
    */
    explicit Protocol(Socket& skt);

    /*
    * Se deshabilita la copia y operador asignacion por copia 
    */
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    /*
    * Metodos virtuales puros de la clase Protocolo.
    */
   virtual void send(GenericMsg* data) = 0;
   virtual GenericMsg* receive() = 0;

    /*
    * Destructor de la clase Protocolo.
    */
    virtual ~Protocol() = default;
};

#endif 
