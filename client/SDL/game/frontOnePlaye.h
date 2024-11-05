#include "../../../common/queue.h"
#include "../../../common/thread.h"
#include "../../../common/messages/generic_msg.h"
#include "map.h"
#include "window.h"
class OnePlayer {
private:

    Queue<GenericMsg*>& queueSend;
    Queue<GenericMsg*>& queueRecive;

    std::string playerName;

public:
    OnePlayer(Queue<GenericMsg*>& queueSend, Queue<GenericMsg*>& queueRecive, std::string playerName);

    void play();
};

