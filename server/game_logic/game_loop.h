#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <chrono>
#include <iostream>
#include <map>
#include <string>

#include "../../common/messages/generic_msg.h"
#include "../../common/messages/handler_read.h"
#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../comunication/send_queues_monitor.h"
#include "config/config.h"
#include "map/spawn_point.h"
#include "map/stage.h"
#include "player/player.h"
class Game;

class GameLoop: public HandlerReader {
private:
    Queue<std::shared_ptr<GenericMsg>>& receiver_q;
    bool is_testing;
    std::map<std::string, Player*> players;

    void create_command();
    std::set<std::string> alive_players;
    void process_commands(Stage& stage);
    std::string look_for_dead_people_and_do_what_you_must(Stage& stage, bool& round_over);
    void sleep_for_round(std::chrono::steady_clock::time_point t0,
                         std::chrono::steady_clock::time_point t1);
    std::vector<std::shared_ptr<WeaponSpawnPoint>> weapon_spawns;
    void spawn_weapons();

    void init_round(Stage& stage, Map& map);
    bool is_cheating;

public:
    explicit GameLoop(Queue<std::shared_ptr<GenericMsg>>&, std::map<std::string, Player*>,
                      bool testing, bool is_cheating);

    std::shared_ptr<GenericMsg> create_msg(const std::string& command);
    void run();
    std::string play_round(Stage& stage, Map& map);

    using HandlerReader::handle_read;

    void cheat();

    void handle_read(const StartActionMsg& msg) override;

    void handle_read(const StopActionMsg& msg) override;

    void handle_read(const StartRoundMsg& msg) override;
};
#endif
