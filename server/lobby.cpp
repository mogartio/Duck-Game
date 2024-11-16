#include "lobby.h"

#include "game_logic/game.h"

#include "client.h"

void Lobby::lobby_empty() {
    if (players_map.size() == EMPTY_PLAYERS) {
        throw std::runtime_error("Lobby vacio");
    }
}

std::list<DescipcionPlayer> Lobby::get_players_description() {
    std::list<DescipcionPlayer> players_description;
    for (auto& pair: players_map) {
        DescipcionPlayer descripcionPlayer;
        descripcionPlayer.nombre = pair.first;
        descripcionPlayer.color = players_colors[pair.first];
        descripcionPlayer.is_ready = players_ready[pair.first];
        players_description.push_back(descripcionPlayer);
    }
    return players_description;
}

Lobby::Lobby(SendQueuesMonitor<GenericMsg*>& send_queues, std::string& player_name, std::string& lobby_name, uint8_t max_players, Client* first_player, uint& id_lobby, bool is_testing):
        send_queues(send_queues),
        receiver_q(new Queue<GenericMsg*>(200)),
        id_lobby(id_lobby),
        is_testing(is_testing) {
    player1_id = first_player->get_id();
    players_map[player_name] = first_player;   
    players_ready[player_name] = GenericMsg::PlayerReadyState::NOT_READY; 
    this->lobby_name = lobby_name;
    this->max_players = max_players;
    players_colors[player_name] = GenericMsg::DuckColor::WHITE;

    send_queues.send_to_client(new EverythingOkMsg, first_player->get_id());
    send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby, GenericMsg::LobbyState::NOT_STARTING), first_player->get_id());
}

void Lobby::addPlayer(std::string& player_name, Client* second_player) {
    lobby_empty();
    if (players_map.size() == max_players) {
        throw std::runtime_error("lobby is full");
    }
    uint cantidadLocalPlayers = 1;
    for (auto& pair: players_map) {
        // Busco los clientes locales (con el mismo id)
        if (pair.second->get_id() == second_player->get_id()) { // si es el mismo cliente...
            // Sumo la cantidad de jugadores locales
            cantidadLocalPlayers++;
            // Si la cantidad de jugadores locales supera el maximo permitido
            if (cantidadLocalPlayers > MAX_LOCAL_PLAYERS) {
                throw std::runtime_error("max local players reached");
            }
        }
        // Si el jugador ya esta en el lobby (por nombre)
        if (pair.first == player_name) {
            throw std::runtime_error("player already in lobby");
        }
    }
    players_map[player_name] = second_player;
    // when adding a new player, pick a color from the available colors
    uint8_t color = *available_colors.begin();
    available_colors.erase(color);
    players_colors[player_name] = color;
    players_ready[player_name] = GenericMsg::PlayerReadyState::NOT_READY;
    send_queues.send_to_client(new EverythingOkMsg(), second_player->get_id());
    send_queues.send_to_client(new PlayerInfoMsg(player_name, color), second_player->get_id());
    std::set<uint8_t> ids;
    for (auto& pair: players_map) {
        if (ids.find(pair.second->get_id()) != ids.end()) {
            continue;
        }
        send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby,GenericMsg::LobbyState::NOT_STARTING), pair.second->get_id());
        ids.insert(pair.second->get_id());
    }
}

void Lobby::removePlayer(std::string player_name) {
    lobby_empty();
    Client* client = players_map[player_name];
    // re-add the color to the available colors
    available_colors.insert(players_colors[player_name]);
    players_ready.erase(player_name);
    // remove the player from the lobby
    int removed = players_map.erase(player_name);
    if (removed != 0) {
        std::set<uint8_t> ids;
        for (auto& pair: players_map) {
            if (ids.find(pair.second->get_id()) != ids.end()) {
                continue;
            }
            send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby, GenericMsg::LobbyState::NOT_STARTING), pair.second->get_id());
            ids.insert(pair.second->get_id());
    }
    } else {
        throw std::runtime_error("Jugador no estaba en el lobby");
    }
    // tell the player he is being removed
    send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby, GenericMsg::LobbyState::NOT_STARTING), client->get_id());
}

void Lobby::startGame() {
    lobby_empty();
    // only start if all players are ready
    for (auto& pair: players_ready) {
        if (pair.second == GenericMsg::PlayerReadyState::NOT_READY) {
            throw std::runtime_error("not all players are ready");
        }
    }
    std::vector<std::string> names;
    std::set<uint> players_ids;  // para no mandarle el mensaje a un jugador dos veces
    for (auto& pair: players_map) {
        if (players_ids.find(pair.second->get_id()) == players_ids.end()) {
            players_ids.insert(pair.second->get_id());
            send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby, GenericMsg::LobbyState::STARTING), pair.second->get_id());
            pair.second->switch_queues(receiver_q); 
        }
        names.push_back(pair.first);
    }
    game = std::make_unique<Game>(*receiver_q, names, is_testing, send_queues);

    game->start();
}

bool Lobby::is_empty() const { return players_map.size() == EMPTY_PLAYERS; }

uint Lobby::getId() const { return id_lobby; }

DescripcionLobby Lobby::getDescription() const {
    DescripcionLobby desc;
    desc.idLobby = id_lobby;
    desc.nombreLobby = lobby_name;
    desc.cantidadJugadores = players_map.size();
    desc.maxJugadores = max_players;
    return desc;
}

void Lobby::updatePlayerInfo(std::string player_name, std::string new_name, uint8_t new_color, uint8_t is_ready) {
    // if the name is already someone else's name, throw error

    if (players_map.find(new_name) != players_map.end() && new_name != player_name) {
        throw std::runtime_error("name already in use");
    }

    // remove old player name key from map and color. First save Client ptr
    Client* client = players_map[player_name];
    players_map.erase(player_name);
    players_colors.erase(player_name);
    // add new player name key to map and color
    players_map[new_name] = client;
    players_colors[new_name] = new_color;
    players_ready[new_name] = is_ready;
    //send all player the updated info
    for (auto& pair: players_map) {
        send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby, GenericMsg::LobbyState::NOT_STARTING), pair.second->get_id());
    }
}