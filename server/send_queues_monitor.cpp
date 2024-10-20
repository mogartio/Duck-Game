#include "send_queues_monitor.h"
template <typename T>
SendQueuesMonitor<T>::SendQueuesMonitor(): m(), send_queues() {}

template <typename T>
void SendQueuesMonitor<T>::add(Queue<T>* queue) {
    std::lock_guard<std::mutex> lock(m);
    send_queues.push_back(queue);
}

template <typename T>
void SendQueuesMonitor<T>::remove(Queue<T>* queue) {
    std::lock_guard<std::mutex> lock(m);
    send_queues.remove(queue);
}

template <typename T>
void SendQueuesMonitor<T>::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    for (Queue<std::string>* queue: send_queues) {
        queue->close();
    }
    send_queues.clear();
}

template <typename T>
void SendQueuesMonitor<T>::broadcast(const std::list<T>& msgs) {
    std::lock_guard<std::mutex> lock(m);
    for (const auto& msg: msgs) {
        for (Queue<T>* queue: send_queues) {
            queue->push(msg);
        }
    }
}
