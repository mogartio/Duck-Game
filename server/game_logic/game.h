#ifndef GAME_H
#define GAME_H

#include <vector>

#include "player/player.h"

#include "game_main.h"
class Game: public Thread {
private:
    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders;
    std::map<std::string, Player*> players;
    std::map<std::string, int> player_points;
    Stage* current_stage;
    std::shared_ptr<GameMain> game_loop;
    std::map<std::string, Player*> generate_players(const std::vector<std::string>& names,
                                                    const PlayerObserver&);
    bool game_over;
    void send_map();

public:
    Game(Queue<std::shared_ptr<GenericMsg>>& recv, const std::vector<std::string>& player_names, bool is_testing,
         SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders);
    void run() override;
};

#endif
