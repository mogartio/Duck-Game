#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <iostream>
#include <string>

#include "../../common/queue.h"
//#include "../../common/thread.h"
#include "../../common/messages/generic_msg.cpp"
#include "../../common/messages/generic_msg.h"
#include "../../common/messages/handler_read.h"
#include "map/csv_writer.h"
#include "map/stage.h"
#include "player/player.h"

class GameMain: public HandlerReader {
private:
    Stage* stage;
    Queue<GenericMsg*>& q;

public:
    explicit GameMain(Queue<GenericMsg*>& q);

    int run();

    using HandlerReader::handle_read;

    void handle_read(const PickupDropMsg& msg) override;

    void handle_read(const StartActionMsg& msg) override;

    void handle_read(const StopActionMsg& msg) override;
};
#endif
