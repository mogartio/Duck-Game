#include "mensaje-lobby.h"

ServerMensajeLobby::ServerMensajeLobby(genericType causa, u_int8_t& tipoMensaje) : MensajeLobby(causa, tipoMensaje) {}

ServerMensajeLobby ServerMensajeLobby::mensajeLobbysDisponibles(std::list<DescripcionLobby> lobbys) {
    u_int8_t lobbys_disponibles = LOBBYS_DISPONIBLES;
    ServerMensajeLobby mensaje(LOBBYMESSAGE, lobbys_disponibles);
    mensaje.lobbys = lobbys;
    return mensaje;
}

ServerMensajeLobby ServerMensajeLobby::todoSalioOkey() {
    u_int8_t todo_salio_okey = TODO_SALIO_OKEY;
    return ServerMensajeLobby(LOBBYMESSAGE, todo_salio_okey);
}

ServerMensajeLobby ServerMensajeLobby::error() {
    u_int8_t error = ERROR;
    return ServerMensajeLobby(LOBBYMESSAGE, error);
}

std::list<DescripcionLobby> ServerMensajeLobby::getLobbys() {
    return lobbys;
}

u_int8_t ServerMensajeLobby::getIdCliente() {
    return idCliente;
}

u_int8_t ServerMensajeLobby::getIdLobby() {
    return idLobby;
}