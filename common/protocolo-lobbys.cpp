#include "protocolo-lobbys.h"
#include "descripcion-lobby.h"

ProtocoloLobbys::ProtocoloLobbys(Socket& socket): ProtocoloCommon(socket) {}

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
    for (auto& lobby: lobbys) {
        send_u_int8_t(lobby.idLobby);
        // send_string(lobby.nombreLobby); este se puede omitir por ahora
        send_u_int8_t(lobby.cantidadJugadores);
    }
}

void ProtocoloLobbys::sendMensajeUnirseALobby(MensajeLobby& mensaje) {
    u_int8_t idLobby = mensaje.getIdLobby();
    send_u_int8_t(idLobby);
}

MensajeLobby ProtocoloLobbys::recvMensajeLobbys() {
    // Falta plantear que necesitaria recibir el cleinte para visualizar las cosas
    u_int8_t type_of_messaje = recv_u_int8_t();
    switch (type_of_messaje) {
        case MensajeLobby::LOBBYS_DISPONIBLES: {
            return recvMensajeLobbysDisponibles();
        }
        case MensajeLobby::UNIRSE_A_LOBBY: {
            return recvMensajeUnirseALobby();
        }
        case MensajeLobby::CREAR_LOBBY: {
            return MensajeLobby::crearMensajeCrearLobby();
        }
        case MensajeLobby::INICIAR_PARTIDA: {
            return MensajeLobby::crearMensajeIniciarPartida();
        }
        case MensajeLobby::SALIR_DE_LOBBY: {
            return MensajeLobby::crearMensajeSalirDeLobby();
        }
    }
}

MensajeLobby ProtocoloLobbys::recvMensajeLobbysDisponibles() {
    std::list<DescripcionLobby> lobbys;
    u_int8_t cant_lobbys = recv_u_int8_t();
    for (int i = 0; i < cant_lobbys; i++) {
        DescripcionLobby lobby;
        u_int8_t idLobby = recv_u_int8_t();
        lobby.idLobby = idLobby;

        // std::string nombreLobby = recv_string(); este se puede omitir por ahora
        u_int8_t cantidadJugadores = recv_u_int8_t();
        lobby.cantidadJugadores = cantidadJugadores;

        lobbys.push_back(lobby);
    }
    return MensajeLobby::crearMensajeLobbysDisponibles(lobbys);
}
