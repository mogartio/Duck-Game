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
    // players_description[FIRST_PLAYER] = descripcionPlayer;
    players_map[player_name] = first_player;    
    this->lobby_name = lobby_name;
    this->max_players = max_players;
    players_colors[player_name] = GenericMsg::DuckColor::WHITE;

    send_queues.send_to_client(new EverythingOkMsg, first_player->get_id());
    send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby), first_player->get_id());
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

    std::set<uint> players_ids;
    for (auto& pair: players_map) {
        if (players_ids.find(pair.second->get_id()) == players_ids.end()) {
            players_ids.insert(pair.second->get_id());
            players_colors[player_name] = GenericMsg::DuckColor::GREY;
            send_queues.send_to_client(new EverythingOkMsg, pair.second->get_id());
            send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby),
                                       pair.second->get_id());
        }
    }
    // players_description[SECOND_PLAYER] = descripcionPlayer;
}

void Lobby::removePlayer(std::string player_name) {
    lobby_empty();
    if (players_map.erase(player_name) != 0) {
        std::set<uint> players_ids;
        for (auto& pair: players_map) {
            if (players_ids.find(pair.second->get_id()) == players_ids.end()) {
                players_ids.insert(pair.second->get_id());
                send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby),
                                           pair.second->get_id());
            }
        }
    } else {
        throw std::runtime_error("Jugador no estaba en el lobby");
    }
}

void Lobby::startGame() {
    lobby_empty();
    // if (players_map.size() != max_players) {
    //     throw std::runtime_error("No se puede iniciar el juego porque menos jugadores de los
    //     necesitados");
    // }
    // Nombres y id de clients
    // std::map<std::string, uint> names;
    std::vector<std::string> names;
    std::set<uint> players_ids;  // para no mandarle el mensaje a un jugador dos veces
    for (auto& pair: players_map) {
        if (players_ids.find(pair.second->get_id()) == players_ids.end()) {
            players_ids.insert(pair.second->get_id());
            send_queues.send_to_client(new InfoLobbyMsg(get_players_description(), max_players, id_lobby),
                                       pair.second->get_id());
            pair.second->switch_queues(
                    receiver_q);  // aca cambiariamos la queue para definir la que
            // se va a pasar a la partida
        }
        names.push_back(pair.first);
        // names[pair.first] = pair.second->get_id();
    }
    // se inicia el juego
    // lanzandose el gameloop aqui
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
