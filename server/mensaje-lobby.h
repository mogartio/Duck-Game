#ifndef SERVERMENSAJELOBBY_H
#define SERVERMENSAJELOBBY_H

#include "./../common/mensaje-lobby.h"


class ServerMensajeLobby : public MensajeLobby {
protected:
    // ------------------ Atributos ----------------------

    std::list<DescripcionLobby> lobbys;

    u_int8_t idCliente;

    u_int8_t idLobby;

    // ------------------ Constructor -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    explicit ServerMensajeLobby(genericType causa, u_int8_t& tipoMensaje);

public:
    // ------------------ Constructor lado server -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    static ServerMensajeLobby mensajeLobbysDisponibles(std::list<DescripcionLobby> lobbys);

    static ServerMensajeLobby todoSalioOkey();

    static ServerMensajeLobby error();

    // ------------------ Constructor lado client -----------------------

    // ------------------ Getters -----------------------
    /*
     * Devuelve la lista de lobbys
     */
    std::list<DescripcionLobby> getLobbys();

    /*
     * Devuelve el id del cliente
     */
    u_int8_t getIdCliente();

    /*
     * Devuelve el id del lobby
     */
    u_int8_t getIdLobby();

    // ------------------ Destructor -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~ServerMensajeLobby() = default;

};
#endif
