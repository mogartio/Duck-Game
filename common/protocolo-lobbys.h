#ifndef PROTOCOLOLOBBYS_H
#define PROTOCOLOLOBBYS_H

#include "mensaje-lobby.h"
#include "protocolo-common.h"

class ProtocoloLobbys: public ProtocoloCommon {
private:
    // ------------------- Atributos -------------------
    // ------------------- Métodos privados -------------------
    void sendMensajeLobbysDisponibles(MensajeLobby& mensaje);

    void sendMensajeUnirseALobby(MensajeLobby& mensaje);

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del protocolo
     */
    explicit ProtocoloLobbys(Socket& socket);

    // ------------------- Métodos públicos -------------------
    /*
     * Envia un mensaje de lobbys a través del socket.
     */
    void sendMensajeLobbys(MensajeLobby& mensaje);

    /*
     * Recibe un mensaje de lobbys a través del socket.
     */
    MensajeLobby recvMensajeLobbys();

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    ProtocoloLobbys(const ProtocoloLobbys&) = delete;
    ProtocoloLobbys& operator=(const ProtocoloLobbys&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    ProtocoloLobbys(ProtocoloLobbys&&) = delete;
    ProtocoloLobbys& operator=(ProtocoloLobbys&&) = delete;

    // ------------------- Destructor -------------------
    /*
     * Destructor del cliente
     */
    ~ProtocoloLobbys() = default;
};
#endif
