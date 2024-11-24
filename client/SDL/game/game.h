#include <algorithm>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

#include "eventhandler.h"
#include "map.h"
#include "window.h"
class Game {
private:
    Queue<std::shared_ptr<GenericMsg>>& queueRecive;
    std::atomic<bool> running;
    EventHandler event_handler;

public:
    Game(Queue<std::shared_ptr<GenericMsg>>& queueSend,
         Queue<std::shared_ptr<GenericMsg>>& queueRecive, std::string playerName1,
         std::string playerName2 = "");

    void play();
};
