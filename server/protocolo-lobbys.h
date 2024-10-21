#ifndef PROTOCOLOLOBBYS_H
#define PROTOCOLOLOBBYS_H

#include "./../common/protocolo-common.h"
#include "mensaje-lobby.h"

class ProtocoloLobbysServer: public ProtocoloCommon {
private:
    // ------------------- Atributos -------------------
    // ------------------- Métodos privados server -------------------

    void sendMensajeLobbysDisponibles(ServerMensajeLobby& mensaje);

    // ------------------- Métodos privados client -------------------

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del protocolo
     */
    explicit ProtocoloLobbysServer(Socket& socket);

    // ------------------- Métodos públicos -------------------
    /*
     * Envia un mensaje de lobbys a través del socket.
     */
    void sendMensajeLobbys(ServerMensajeLobby& mensaje);

    /*
     * Recibe un mensaje de lobbys a través del socket.
     */
    //MensajeLobby recvMensajeLobbys(); implementar aca la idea del cliente

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    ProtocoloLobbysServer(const ProtocoloLobbysServer&) = delete;
    ProtocoloLobbysServer& operator=(const ProtocoloLobbysServer&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    ProtocoloLobbysServer(ProtocoloLobbysServer&&) = delete;
    ProtocoloLobbysServer& operator=(ProtocoloLobbysServer&&) = delete;

    // ------------------- Destructor -------------------
    /*
     * Destructor del cliente
     */
    ~ProtocoloLobbysServer() = default;
};
#endif