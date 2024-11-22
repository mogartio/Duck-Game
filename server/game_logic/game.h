#ifndef GAME_H
#define GAME_H

#include <vector>

#include "./map/map_manager.h"
#include "player/player.h"

#include "game_main.h"
class Game: public Thread {
private:
    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders;
    Queue<std::shared_ptr<GenericMsg>>& recv;

    std::vector<std::string> player_names;
    std::map<std::string, Player*> players;
    std::map<std::string, int> player_points;
    std::shared_ptr<std::set<uint>> ids;

    Stage* current_stage;
    std::shared_ptr<GameMain> game_loop;

    bool game_over;
    bool is_testing;
    bool players_created;

    MapManager map_manager;

    void send_map(Map& map);
    std::map<std::string, Player*> generate_players(const std::vector<std::string>& names,
                                                const PlayerObserver&, Map& map);

public:
    Game(Queue<std::shared_ptr<GenericMsg>>& recv, const std::vector<std::string>& player_names,
         bool is_testing, SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders,
         std::shared_ptr<std::set<uint>> ids);
    void run() override;
};

#endif
