#include "common/queue.h"
#include "common/thread.h"
#include "map.h"

class OnePlayer: Thread {
private:

    Queue<Front_event>& queueSend;
    Queue<int>& queueRecive;

    void run() override;

public:
    OnePlayer(Queue<Front_event>& queueSend, Queue<int>& queueRecive);

};

