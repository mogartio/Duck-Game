#include "mensaje-lobby.h"

ServerMensajeLobby::ServerMensajeLobby(u_int8_t &tipoMensaje) : MensajeLobby(tipoMensaje){}

ServerMensajeLobby::ServerMensajeLobby(u_int8_t &tipoMensaje, u_int8_t &idLobby) : MensajeLobby(tipoMensaje,idLobby){}

ServerMensajeLobby::ServerMensajeLobby(u_int8_t &tipoMensaje, std::list<DescripcionLobby> &lobbys) : MensajeLobby(tipoMensaje,lobbys){}

u_int8_t ServerMensajeLobby::getIdCliente() {
    return idCliente;
}

void ServerMensajeLobby::setIdCliente(u_int8_t idCliente) {
    ServerMensajeLobby::idCliente = idCliente;
}
