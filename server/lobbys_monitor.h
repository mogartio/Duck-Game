#ifndef LOBBYS_MONITOR_H
#define LOBBYS_MONITOR_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

#include "lobby.h"

class LobbysMonitor {
private:
    std::mutex m;
    std::list<Lobby> lobbys_disponibles;
    // va aumentando asi cada lobby tiene un id unico
    uint contador_id_lobbys;

public:
    LobbysMonitor();
    // Devuelve la lista de lobbys disponibles
    std::vector<DescripcionLobby> get_lobbys();
    // Agrega un lobby a la lista de lobbys disponibles y devuelve el id del lobby
    uint create(std::tuple<std::string, uint> player);
    // Agrega un jugador a un lobby
    void add_player(uint id_lobby, std::tuple<std::string, uint> player);
    // Elimina un jugador de un lobby
    void remove_player(uint id_lobby, std::tuple<std::string, uint> player);
    // Iniciar el lobby
    void start_game(uint id_lobby);
    // Elimina los lobbys que estan vacios
    void remove_dead_lobbys();
    // Elimina todos los lobbys
    void remove_all();

    ~LobbysMonitor();
};
#endif  // CLIENTS_MONITOR_H
