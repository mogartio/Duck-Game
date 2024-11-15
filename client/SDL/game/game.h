#include <string>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

#include "eventhandler.h"
#include "map.h"
#include "window.h"
class Game {
private:
    Queue<GenericMsg*>& queueRecive;
    std::atomic<bool> running;
    EventHandler event_handler;

public:
    Game(Queue<GenericMsg*>& queueSend, Queue<GenericMsg*>& queueRecive,
              std::string playerName1, std::string playerName2 = "");

    void play();
};
