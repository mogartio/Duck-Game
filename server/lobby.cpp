#include "lobby.h"

Lobby::Lobby(Client* client, u_int8_t& idlobby) : jugadores(), id_lobby(idlobby) {
    jugadores.push_back(client);
}

void Lobby::lobby_empty() {
    if (jugadores.size() == EMPTY_PLAYERS){
        throw std::runtime_error("Lobby vacio");
    }
}

void Lobby::addPlayer(Client* client) {
    lobby_empty();
    if (jugadores.size() == MAX_PLAYERS) {
        throw std::runtime_error("Lobby lleno");
    }
    jugadores.push_back(client);
}

void Lobby::removePlayer(Client* client) {
    lobby_empty();
    jugadores.remove(client);
}

void Lobby::startGame() {
    lobby_empty();
    // se inicia el juego
    // lanzandose el gameloop aqui
}

void Lobby::closeLobby() {
    // se cierra el gameloop aqui
    // se elimina a los jugadores
    jugadores.clear();
}

bool Lobby::is_empty() const {
    return jugadores.size() == EMPTY_PLAYERS;
}

u_int8_t Lobby::getId() const {
    return id_lobby;
}

DescripcionLobby Lobby::getDescription() const {
    DescripcionLobby desc;
    desc.idLobby = id_lobby;
    desc.cantidadJugadores = jugadores.size();
    desc.nombreLobby = "Lobby " + std::to_string(id_lobby); // nombre generico por ahora
    return desc;
}
