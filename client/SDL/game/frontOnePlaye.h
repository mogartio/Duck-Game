#include "../../../common/queue.h"
#include "../../../common/thread.h"

class OnePlayer {
private:

    Queue<Front_event>& queueSend;
    Queue<int>& queueRecive;

    std::string playerName;

public:
    OnePlayer(Queue<Front_event>& queueSend, Queue<int>& queueRecive, std::string playerName);

    void play();
};

