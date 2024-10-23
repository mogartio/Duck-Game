#include "protocolo-lobbys.h"

#include <stdexcept>

ProtocoloLobbysServer::ProtocoloLobbysServer(Socket& socket, u_int8_t& idCliente):
        Protocol(socket), idCliente(idCliente) {}

void ProtocoloLobbysServer::sendMensajeLobbysDisponibles(ServerMensajeLobby& mensaje) {
    if (static_cast<int>(mensaje.getTipeHeader()) !=
        static_cast<int>(ServerMensajeLobby::LOBBYS_DISPONIBLES)) {
        return;
    }
    u_int8_t cantidadLobbys = mensaje.getLobbys().size();
    send_uint8_t(cantidadLobbys);
    for (auto& lobby: mensaje.getLobbys()) {
        send_uint8_t(lobby.idLobby);
        send_string(lobby.nombreLobby);
        send_uint8_t(lobby.cantidadJugadores);
    }
}

void ProtocoloLobbysServer::sendMensajeLobbys(ServerMensajeLobby& mensaje) {
    u_int8_t causa = mensaje.getTipeHeader();
    send_uint8_t(causa);

    u_int8_t tipoMensaje = mensaje.getTipoMensaje();
    send_uint8_t(tipoMensaje);

    sendMensajeLobbysDisponibles(mensaje);
}

ServerMensajeLobby ProtocoloLobbysServer::recvMensajeLobbys() {
    u_int8_t header = recv_uint8_t();
    if (static_cast<int>(header) != static_cast<int>(ServerMensajeLobby::LOBBYMESSAGE)) {
        throw std::runtime_error("Este header no es valido para este protocolo");
    }

    u_int8_t tipoMensaje = recv_uint8_t();

    if (static_cast<int>(tipoMensaje) == static_cast<int>(ServerMensajeLobby::UNIRSE_A_LOBBY)) {
        u_int8_t idLobby = recv_uint8_t();
        ServerMensajeLobby devolverMensaje(tipoMensaje, idLobby);
        devolverMensaje.setIdCliente(idCliente);
        return devolverMensaje;
    } else {
        ServerMensajeLobby devolverMensaje(tipoMensaje);
        devolverMensaje.setIdCliente(idCliente);
        return devolverMensaje;
    }
}
