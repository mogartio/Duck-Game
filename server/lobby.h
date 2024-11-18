#ifndef LOBBY_H
#define LOBBY_H

#include <array>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

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
    std::map<std::string, uint8_t> players_colors;
    std::map<std::string, uint8_t> players_ready;

    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& send_queues;
    std::set<uint8_t> available_colors = {GenericMsg::DuckColor::YELLOW,
                                          GenericMsg::DuckColor::ORANGE,
                                          GenericMsg::DuckColor::GREY};
    Queue<std::shared_ptr<GenericMsg>>* receiver_q;

    std::shared_ptr<Game> game;

    uint player1_id;

    uint id_lobby;

    std::string lobby_name;
    uint8_t max_players;

    void lobby_empty();
    bool is_testing;
    bool is_dead;

    std::list<DescipcionPlayer> get_players_description();

public:
    /*
     * Constructor del lobby
     */
    explicit Lobby(SendQueuesMonitor<std::shared_ptr<GenericMsg>>& send_queues,
                   std::string& player_name, std::string& lobby_name, uint8_t max_players,
                   Client* first_player, uint& id_lobby, bool is_testing);

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

    /*
     * Metodo que actualiza la informacion de un jugador
     */
    void updatePlayerInfo(std::string player_name, std::string new_name, uint8_t color,
                          uint8_t is_ready);

    /*
     * Metodo que elimina el lobby y todo su contenido
     */
    void kill();

    // ------------------ Desabilitamos -----------------------

    /*
     * Destructor del aceptador del servidor
     */
    ~Lobby() = default;
};
#endif
