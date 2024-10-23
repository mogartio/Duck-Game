#include "mensaje-lobby.h"

#include <stdexcept>

void MensajeLobby::validarTipoMensaje(u_int8_t& tipoMensaje) const {
    if (tipoMensaje < VER_LOBBYS || tipoMensaje > ERROR) {
        throw std::invalid_argument("Tipo de mensaje del lobby invalido");
    }
}

MensajeLobby::MensajeLobby(u_int8_t& tipoMensaje) : Mensaje(LOBBYMESSAGE), tipoMensaje(tipoMensaje) {
    validarTipoMensaje(tipoMensaje);
    if (tipoMensaje == UNIRSE_A_LOBBY || tipoMensaje == LOBBYS_DISPONIBLES) {
        throw std::invalid_argument("Tipo de mensaje del lobby invalido");
    }
}

u_int8_t MensajeLobby::getTipoMensaje() const {
    return tipoMensaje;
}

MensajeLobby::MensajeLobby(u_int8_t& tipoMensaje, u_int8_t& idLobby) : Mensaje(LOBBYMESSAGE), tipoMensaje(tipoMensaje), idLobby(idLobby) {
    validarTipoMensaje(tipoMensaje);
    if (tipoMensaje != UNIRSE_A_LOBBY) {
        throw std::invalid_argument("Tipo de mensaje del lobby invalido");
    }
}

u_int8_t MensajeLobby::getIdLobby() const{
    return idLobby;
}

MensajeLobby::MensajeLobby(u_int8_t& tipoMensaje, std::list<DescripcionLobby>& lobbys) : Mensaje(LOBBYMESSAGE), tipoMensaje(tipoMensaje), lobbys(lobbys) {
    validarTipoMensaje(tipoMensaje);
    if (tipoMensaje != LOBBYS_DISPONIBLES) {
        throw std::invalid_argument("Tipo de mensaje del lobby invalido");
    }
}

std::list<DescripcionLobby> MensajeLobby::getLobbys() const {
    return lobbys;
}
