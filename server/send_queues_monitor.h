#ifndef SEND_QUEUES_MONITOR_H
#define SEND_QUEUES_MONITOR_H


#include <list>
#include <mutex>

#include "../common/queue.h"

template <typename T>
class SendQueuesMonitor {
private:
    std::mutex m;
    std::list<Queue<T>*> send_queues;

public:
    SendQueuesMonitor();
    void add(Queue<T>* queue);
    void remove(Queue<T>* queue);
    void broadcast(const std::list<T>& msgs);
    void remove_all();
};

#endif  // SEND_QUEUES_MONITOR_H
