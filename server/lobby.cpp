#include "lobby.h"

Lobby::Lobby(std::tuple<std::string, uint> player1, uint& id_lobby): id_lobby(id_lobby) {
    DescipcionPlayer player1_desc;
    player1_desc.nombre = std::get<0>(player1);
    player1_desc.id = std::get<1>(player1);
    player1_desc.color = 0;  // color del player1
    players.push_back(player1_desc);
}

void Lobby::lobby_empty() {
    if (players.size() == EMPTY_PLAYERS) {
        throw std::runtime_error("Lobby vacio");
    }
}

void Lobby::addPlayer(std::tuple<std::string, uint> player2) {
    lobby_empty();
    if (players.size() == MAX_PLAYERS) {
        throw std::runtime_error("Lobby lleno");
    }
    for (auto& player: players) {
        if (player.id == std::get<1>(player2) && player.nombre == std::get<0>(player2)) {
            throw std::runtime_error("Jugador ya estaba en el lobby");
        }
    }
    DescipcionPlayer player2_desc;
    player2_desc.nombre = std::get<0>(player2);
    player2_desc.id = std::get<1>(player2);
    player2_desc.color = 1;  // color del player2
    players.push_back(player2_desc);
}

void Lobby::removePlayer(std::tuple<std::string, uint> player) {
    lobby_empty();
    players.remove_if([player](DescipcionPlayer& p) {
        return p.id == std::get<1>(player) && p.nombre == std::get<0>(player);
    });
}

void Lobby::startGame() {
    lobby_empty();
    // se inicia el juego
    // lanzandose el gameloop aqui
}

bool Lobby::is_empty() const { return players.size() == EMPTY_PLAYERS; }

uint Lobby::getId() const { return id_lobby; }

DescripcionLobby Lobby::getDescription() const {
    DescripcionLobby desc;
    desc.idLobby = id_lobby;
    desc.cantidadJugadores = players.size();
    desc.player1 = players.front();
    if (players.size() == MAX_PLAYERS) {
        auto it = players.begin();
        it++;
        desc.player2 = *it;
    }
    // desc.nombreLobby = "Lobby " + std::to_string(id_lobby);  // nombre generico por ahora
    return desc;
}
