#include "send_queues_monitor.h"

SendQueuesMonitor::SendQueuesMonitor() : m(), send_queues() {}

void SendQueuesMonitor::add(Queue<std::string>* queue) {
    std::lock_guard<std::mutex> lock(m);
    send_queues.push_back(queue);
}

void SendQueuesMonitor::remove(Queue<std::string>* queue) {
    std::lock_guard<std::mutex> lock(m);
    send_queues.remove(queue);
}

void SendQueuesMonitor::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    for (Queue<std::string>* queue : send_queues) {
        queue->close();
    }
    send_queues.clear();
}