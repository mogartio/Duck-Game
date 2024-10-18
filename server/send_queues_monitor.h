#ifndef SEND_QUEUES_MONITOR_H
#define SEND_QUEUES_MONITOR_H


#include <mutex>
#include <list>
#include "../common/queue.h"

class SendQueuesMonitor {
private:
    std::mutex m;
    std::list<Queue<std::string>*> send_queues;
public:
    SendQueuesMonitor();
    void add(Queue<std::string>* queue);
    void remove(Queue<std::string>* queue);
    void remove_all();
};

#endif // SEND_QUEUES_MONITOR_H
