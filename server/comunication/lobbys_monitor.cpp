#include "lobbys_monitor.h"


LobbysMonitor::LobbysMonitor(bool is_testing):
        m(), lobbys_disponibles(), contador_id_lobbys(0), is_testing(is_testing) {}

std::vector<DescripcionLobby> LobbysMonitor::get_lobbys() {
    std::lock_guard<std::mutex> lock(m);
    std::vector<DescripcionLobby> lobbys_disponibles_descripcion;
    for (auto& lobby: lobbys_disponibles) {
        lobbys_disponibles_descripcion.push_back(lobby.second->getDescription());
    }
    return lobbys_disponibles_descripcion;
}

uint LobbysMonitor::create(SendQueuesMonitor<std::shared_ptr<GenericMsg>>& send_queues,
                           std::string& player_name, std::string& lobby_name, uint8_t max_players,
                           Client* first_player) {
    std::lock_guard<std::mutex> lock(m);
    contador_id_lobbys++;
    lobbys_disponibles.emplace(
            contador_id_lobbys,
            std::make_shared<Lobby>(send_queues, player_name, lobby_name, max_players, first_player,
                                    contador_id_lobbys, is_testing));
    return contador_id_lobbys;
}

void LobbysMonitor::add_player(uint id_lobby, std::string& player_name, Client* second_player) {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.at(id_lobby)->addPlayer(player_name, second_player);
}

void LobbysMonitor::remove_player(uint id_lobby, std::string player_name) {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.at(id_lobby)->removePlayer(player_name);
}

void LobbysMonitor::start_game(uint id_lobby) {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.at(id_lobby)->startGame();
}

void LobbysMonitor::remove_lobby(uint id_lobby) {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.at(id_lobby)->kill();
    lobbys_disponibles.erase(id_lobby);
}

void LobbysMonitor::remove_dead_lobbys() {
    std::lock_guard<std::mutex> lock(m);
    std::list<uint> lobbys_a_eliminar;
    for (auto& lobby: lobbys_disponibles) {
        if (lobby.second->is_empty()) {
            lobbys_a_eliminar.push_back(lobby.first);
        }
    }

    for (uint id_lobby: lobbys_a_eliminar) {
        lobbys_disponibles.erase(id_lobby);
    }
}

void LobbysMonitor::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.clear();
}

void LobbysMonitor::update_player_info(uint lobby_id, std::string player_name, std::string new_name,
                                       uint8_t color, uint8_t is_ready) {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.at(lobby_id)->updatePlayerInfo(player_name, new_name, color, is_ready);
}

LobbysMonitor::~LobbysMonitor() { remove_all(); }
