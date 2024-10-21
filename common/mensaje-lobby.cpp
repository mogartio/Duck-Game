#include "mensaje-lobby.h"

#include <stdexcept>

MensajeLobby::MensajeLobby(genericType causa, u_int8_t tipoMensaje) : Mensaje(causa), tipoMensaje(tipoMensaje) {
    if (tipoMensaje < VER_LOBBYS || tipoMensaje > ERROR) {
        throw std::invalid_argument("Tipo de mensaje del lobby invalido");
    }
}

u_int8_t MensajeLobby::getTipoMensaje() const {
    return tipoMensaje;
}
