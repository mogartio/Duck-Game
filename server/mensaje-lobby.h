#ifndef SERVERMENSAJELOBBY_H
#define SERVERMENSAJELOBBY_H

#include "./../common/queuesStructs/mensaje-lobby.h"


class ServerMensajeLobby : public MensajeLobby {
protected:
    // ------------------ Atributos ----------------------

    u_int8_t idCliente;

public:
    // ------------------ Constructor lado server -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    ServerMensajeLobby(u_int8_t tipoMensaje, u_int8_t idCliente);

    // ------------------ Constructor lado client -----------------------

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
