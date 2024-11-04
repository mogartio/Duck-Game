#include "common/queue.h"

class StartUp{
private:

    Queue<std::string>& queueSend;
    Queue<std::string>& queueRecive;

public:
    StartUp(Queue<std::string>& queueSend, Queue<std::string>& queueRecive);

};


