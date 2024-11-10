#ifndef LOBBYS_MONITOR_H
#define LOBBYS_MONITOR_H

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "lobby.h"

class LobbysMonitor {
private:
    std::mutex m;
    std::map<uint, std::unique_ptr<Lobby>> lobbys_disponibles;
    // va aumentando asi cada lobby tiene un id unico
    uint contador_id_lobbys;
    bool is_testing;

public:
    LobbysMonitor(bool);
    // Devuelve la lista de lobbys disponibles
    std::vector<DescripcionLobby> get_lobbys();
    // Agrega un lobby a la lista de lobbys disponibles y devuelve el id del lobby
    uint create(SendQueuesMonitor<GenericMsg*>& send_queues, std::string& player_name,
                Client* first_player);
    // Agrega un jugador a un lobby
    void add_player(uint id_lobby, std::string& player_name, Client* second_player);
    // Elimina un jugador de un lobby
    void remove_player(uint id_lobby, std::string player_name);
    // Iniciar el lobby
    void start_game(uint id_lobby);
    // Elimina los lobbys que estan vacios
    void remove_dead_lobbys();
    // Elimina todos los lobbys
    void remove_all();

    ~LobbysMonitor();
};
#endif  // CLIENTS_MONITOR_H
