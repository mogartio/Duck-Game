#include "protocolo-lobbys.h"

ProtocoloLobbysServer::ProtocoloLobbysServer(Socket &socket) : ProtocoloCommon(socket) {}

void ProtocoloLobbysServer::sendMensajeLobbysDisponibles(ServerMensajeLobby &mensaje) {
    if (static_cast<int>(mensaje.getTipeHeader()) != static_cast<int>(ServerMensajeLobby::LOBBYS_DISPONIBLES)){
        return;
    }
    u_int8_t cantidadLobbys = mensaje.getLobbys().size();
    send_u_int8_t(cantidadLobbys);
    for (auto &lobby : mensaje.getLobbys()) {
        send_u_int8_t(lobby.idLobby);
        send_string(lobby.nombreLobby);
        send_u_int8_t(lobby.cantidadJugadores);
    }
}

void ProtocoloLobbysServer::sendMensajeLobbys(ServerMensajeLobby &mensaje) {
    u_int8_t causa = mensaje.getTipeHeader();
    send_u_int8_t(causa);

    u_int8_t tipoMensaje = mensaje.getTipoMensaje();
    send_u_int8_t(tipoMensaje);

    sendMensajeLobbysDisponibles(mensaje);
}
