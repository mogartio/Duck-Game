#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <iostream>
#include <map>
#include <string>

#include "../../common/messages/generic_msg.h"
#include "../../common/messages/handler_read.h"
#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../send_queues_monitor.h"
#include "config/config.h"
#include "map/csv_writer.h"
#include "map/stage.h"
#include "player/player.h"

class GameMain: public HandlerReader {
private:
    Queue<GenericMsg*>& receiver_q;
    bool is_testing;
    std::map<std::string, Player*> players;
    SendQueuesMonitor<GenericMsg*>& senders;
    void create_command();

public:
    explicit GameMain(Queue<GenericMsg*>&, std::map<std::string, Player*>, bool,
                      SendQueuesMonitor<GenericMsg*>&);

    GenericMsg* create_msg(std::string command);
    void run();
    std::string play_round(Stage&);

    using HandlerReader::handle_read;

    void handle_read(const PickupDropMsg& msg) override;

    void handle_read(const StartActionMsg& msg) override;

    void handle_read(const StopActionMsg& msg) override;
};
#endif
