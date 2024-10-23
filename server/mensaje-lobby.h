#ifndef SERVERMENSAJELOBBY_H
#define SERVERMENSAJELOBBY_H
#include <list>

#include "./../common/messages/mensaje-lobby.h"


class ServerMensajeLobby: public MensajeLobby {
protected:
    // ------------------ Atributos ----------------------
    u_int8_t idCliente;

public:
    // ------------------ Constructor -----------------------
    explicit ServerMensajeLobby(u_int8_t& tipoMensaje);

    explicit ServerMensajeLobby(u_int8_t& tipoMensaje, u_int8_t& idLobby);

    explicit ServerMensajeLobby(u_int8_t& tipoMensaje, std::list<DescripcionLobby>& lobbys);
    // ------------------ Getters -----------------------
    /*
     * Devuelve el id del cliente
     */
    u_int8_t getIdCliente();

    /*
     * Setea el id del cliente
     */
    void setIdCliente(u_int8_t idCliente);

    // ------------------ Destructor -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~ServerMensajeLobby() = default;
};
#endif
