#include "lobby.h"

#include "client.h"

Lobby::Lobby(SendQueuesMonitor<GenericMsg*>& send_queues, std::string& player_name,
             Client* first_player, uint& id_lobby):
        send_queues(send_queues), id_lobby(id_lobby) {
    player1_id = first_player->get_id();
    // players_description[FIRST_PLAYER] = descripcionPlayer;
    players_map[player_name] = first_player;
}

void Lobby::lobby_empty() {
    if (players_map.size() == EMPTY_PLAYERS) {
        throw std::runtime_error("Lobby vacio");
    }
}

void Lobby::addPlayer(std::string& player_name, Client* second_player) {
    lobby_empty();
    if (players_map.size() == MAX_PLAYERS) {
        throw std::runtime_error("Lobby lleno");
    }
    players_map.find(player_name) == players_map.end() ?
            players_map[player_name] = second_player :
            throw std::runtime_error("Jugador ya estaba en el lobby");
    // players_description[SECOND_PLAYER] = descripcionPlayer;
}

void Lobby::removePlayer(std::string player_name) {
    lobby_empty();
    players_map.erase(player_name);
}

void Lobby::startGame() {
    lobby_empty();
    // se inicia el juego
    // lanzandose el gameloop aqui
}

bool Lobby::is_empty() const { return players_map.size() == EMPTY_PLAYERS; }

uint Lobby::getId() const { return id_lobby; }

DescripcionLobby Lobby::getDescription() const {
    DescripcionLobby desc;
    desc.idLobby = id_lobby;
    desc.cantidadJugadores = players_map.size();
    // desc.player1 = players_description[FIRST_PLAYER];
    // desc.player2 = players_description[SECOND_PLAYER];
    return desc;
}
