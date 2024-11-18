#ifndef PROTOCOLOCOMMON_H
#define PROTOCOLOCOMMON_H
#include <functional>
#include <map>
#include <string>
#include <memory>

#include "./messages/generic_msg.h"
#include "./messages/handler_recv.h"
#include "./messages/handler_send.h"
#include "./socket/socket.h"
#include "./socket/socket_error.h"

class ProtocoloCommon: public HandlerSender, public HandlerReceiver {
private:
    // ------------------- Atributos -------------------

    Socket& socket;

    std::map<GenericMsg::MsgTypeHeader, std::function<std::shared_ptr<GenericMsg>()>> recv_handlers;

    // ------------------- Métodos privados -------------------

    /*
     * Lanza SocketError en caso de que el socket se haya cerrado al enviar o recibir datos.
     */
    void chk_closed_andif_fail(const char error_ms[]) const;

protected:
    // ------------------- Atributos -------------------

    bool was_closed;

    // ------------------- Métodos protegidos -------------------

    /*
     * Envia un u_int8_t a través del socket.
     */
    void send_u_int8_t(u_int8_t& data);

    /*
     * Recibe un u_int8_t a través del socket.
     */
    u_int8_t recv_u_int8_t();

    /*
     * Envia un u_int16_t a través del socket.
     */
    void send_u_int16_t(u_int16_t& data);

    /*
     * Recibe un u_int16_t a través del socket.
     */
    u_int16_t recv_u_int16_t();

    /*
     * Envia un string a través del socket.
     */
    void send_string(std::string& data);

    /*
     * Recibe un string a través del socket.
     */
    std::string recv_string();

public:
    // ------------------- Métodos públicos -------------------

    void send(std::shared_ptr<GenericMsg> msg);

    std::shared_ptr<GenericMsg> receive();

    // ------------------- Constructor -------------------
    /*
     * Constructor del protocolo
     */
    explicit ProtocoloCommon(Socket& socket);

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    ProtocoloCommon(const ProtocoloCommon&) = delete;
    ProtocoloCommon& operator=(const ProtocoloCommon&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    ProtocoloCommon(ProtocoloCommon&&) = delete;
    ProtocoloCommon& operator=(ProtocoloCommon&&) = delete;

    // ------------------- Destructor -------------------
    /*
     * Destructor del cliente
     */
    ~ProtocoloCommon() = default;
};
#endif
