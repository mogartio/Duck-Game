#ifndef LOBBY_H
#define LOBBY_H

#include <array>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>

#include "./../common/messages/descripcion-lobby.h"
#include "./../common/messages/generic_msg.h"
#include "./../common/queue.h"
#include "./game_logic/game_main.h"
#include "game_logic/game.h"

#include "send_queues_monitor.h"

#define MAX_LOCAL_PLAYERS 2
#define EMPTY_PLAYERS 0
#define FIRST_PLAYER 0
#define SECOND_PLAYER 1
class Client;

class Lobby {
private:
    std::map<std::string, Client*> players_map;

    SendQueuesMonitor<GenericMsg*>& send_queues;

    Queue<GenericMsg*>* receiver_q;

    std::unique_ptr<Game> game;

    uint player1_id;

    uint id_lobby;

    std::string lobby_name;
    uint8_t max_players;

    void lobby_empty();
    bool is_testing;

    std::list<DescipcionPlayer> get_players_description();

public:
    /*
     * Constructor del lobby
     */
    explicit Lobby(SendQueuesMonitor<GenericMsg*>& send_queues, std::string& player_name, std::string& lobby_name, uint8_t max_players, Client* first_player, uint& id_lobby, bool is_testing);

    /*
     * Metodo que agrega un jugador al lobby
     */
    void addPlayer(std::string& player_name, Client* second_player);

    /*
     * Metodo que elimina un jugador del lobby
     */
    void removePlayer(std::string player_name);

    /*
     * Metodo que inicia el juego
     */
    void startGame();

    /*
     * Metodo que devuelve si el lobby esta vacio
     */
    bool is_empty() const;

    /*
     * Metodo que devuelve el id del lobby
     */
    uint getId() const;

    /*
     * Metodo que devuelve la descripcion del lobby
     */
    DescripcionLobby getDescription() const;

    // ------------------ Desabilitamos -----------------------

    /*
     * Destructor del aceptador del servidor
     */
    ~Lobby() = default;
};
#endif
