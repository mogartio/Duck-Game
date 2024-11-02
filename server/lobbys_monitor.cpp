#include "lobbys_monitor.h"


LobbysMonitor::LobbysMonitor(): m(), lobbys_disponibles(), contador_id_lobbys(0) {}

std::list<DescripcionLobby> LobbysMonitor::get_lobbys() {
    std::lock_guard<std::mutex> lock(m);
    std::list<DescripcionLobby> lobbys_disponibles_descripcion;
    for (const Lobby& lobby: lobbys_disponibles) {
        lobbys_disponibles_descripcion.push_back(lobby.getDescription());
    }
    return lobbys_disponibles_descripcion;
}

uint LobbysMonitor::create(std::tuple<std::string, uint> player) {
    std::lock_guard<std::mutex> lock(m);
    contador_id_lobbys++;
    lobbys_disponibles.emplace_back(player, contador_id_lobbys);
    return contador_id_lobbys;
}

void LobbysMonitor::add_player(uint id_lobby, std::tuple<std::string, uint> player) {
    std::lock_guard<std::mutex> lock(m);
    for (Lobby& lobby: lobbys_disponibles) {
        if (lobby.getId() == id_lobby) {
            lobby.addPlayer(player);
            return;
        }
    }
}

void LobbysMonitor::remove_player(uint id_lobby, std::tuple<std::string, uint> player) {
    std::lock_guard<std::mutex> lock(m);
    for (Lobby& lobby: lobbys_disponibles) {
        if (lobby.getId() == id_lobby) {
            lobby.removePlayer(player);
            return;
        }
    }
}

void LobbysMonitor::start_game(uint id_lobby) {
    std::lock_guard<std::mutex> lock(m);
    for (Lobby& lobby: lobbys_disponibles) {
        if (lobby.getId() == id_lobby) {
            lobby.startGame();
            return;
        }
    }
}

void LobbysMonitor::remove_dead_lobbys() {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.remove_if([](const Lobby& lobby) { return lobby.is_empty(); });
}

void LobbysMonitor::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    lobbys_disponibles.clear();
}

LobbysMonitor::~LobbysMonitor() { remove_all(); }
