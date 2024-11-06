#include <string>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

#include "map.h"
#include "window.h"
class OnePlayer {
private:
    Queue<GenericMsg*>& queueRecive;
    std::string playerName;
    std::atomic<bool>& running;

public:
    OnePlayer(Queue<GenericMsg*>& queueRecive, std::string playerName, std::atomic<bool>& running);

    void play();
};
