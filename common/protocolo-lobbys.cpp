#include "protocolo-lobbys.h"

ProtocoloLobbys::ProtocoloLobbys(Socket& socket) : ProtocoloCommon(socket) {}

void ProtocoloLobbys::sendMensajeLobbys(MensajeLobby& mensaje) {
    u_int8_t type_of_messaje = mensaje.getTipo();
    send_u_int8_t(type_of_messaje);
    switch (type_of_messaje) {
        case MensajeLobby::LOBBYS_DISPONIBLES: {
            sendMensajeLobbysDisponibles(mensaje);
            break;
        }
        case MensajeLobby::UNIRSE_A_LOBBY: {
            sendMensajeUnirseALobby(mensaje);
            break;
        }
    }
}

void ProtocoloLobbys::sendMensajeLobbysDisponibles(MensajeLobby& mensaje) {
    std::list<DescripcionLobby> lobbys = mensaje.getLobbys();
    u_int8_t cant_lobbys = lobbys.size();
    send_u_int8_t(cant_lobbys);
    for (auto& lobby : lobbys) {
        send_u_int8_t(lobby.idLobby);
        //send_string(lobby.nombreLobby); este se puede omitir por ahora
        send_u_int8_t(lobby.cantidadJugadores);
    }
}

void ProtocoloLobbys::sendMensajeUnirseALobby(MensajeLobby& mensaje) {
    u_int8_t idLobby = mensaje.getIdLobby();
    send_u_int8_t(idLobby);
}

MensajeLobby ProtocoloLobbys::recvMensajeLobbys() {
    // Falta plantear que necesitaria recibir el cleinte para visualizar las cosas
}
