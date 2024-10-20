#include "mensaje-lobby.h"

MensajeLobby MensajeLobby::crearMensajeLobbysDisponibles(std::list<DescripcionLobby> lobbys) {
    MensajeLobby mensaje;
    mensaje.tipo = LOBBYS_DISPONIBLES;
    mensaje.lobbys = lobbys;
    return mensaje;
}

MensajeLobby MensajeLobby::crearMensajeCrearLobby() {
    MensajeLobby mensaje;
    mensaje.tipo = CREAR_LOBBY;
    return mensaje;
}

MensajeLobby MensajeLobby::crearMensajeUnirseALobby(u_int8_t idLobby) {
    MensajeLobby mensaje;
    mensaje.tipo = UNIRSE_A_LOBBY;
    mensaje.idLobby = idLobby;
    return mensaje;
}

MensajeLobby MensajeLobby::crearMensajeIniciarPartida() {
    MensajeLobby mensaje;
    mensaje.tipo = INICIAR_PARTIDA;
    return mensaje;
}

MensajeLobby MensajeLobby::crearMensajeSalirDeLobby() {
    MensajeLobby mensaje;
    mensaje.tipo = SALIR_DE_LOBBY;
    return mensaje;
}

u_int8_t MensajeLobby::getTipo() const {
    return tipo;
}

u_int8_t MensajeLobby::getIdLobby() const {
    return idLobby;
}

u_int8_t MensajeLobby::getIdCliente() const {
    return idCliente;
}

void MensajeLobby::setIdCliente(u_int8_t idCliente) {
    this->idCliente = idCliente;
}

std::list<DescripcionLobby> MensajeLobby::getLobbys() const {
    return lobbys;
}


