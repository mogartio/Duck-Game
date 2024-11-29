#ifndef SEND_QUEUES_MONITOR_H
#define SEND_QUEUES_MONITOR_H

#include <list>
#include <map>
#include <mutex>

#include "../../common/queue.h"

template <typename T>
class SendQueuesMonitor {
private:
    std::mutex m;
    std::map<int, Queue<T>*> send_queues_map;  // <client_id, send_queue>
public:
    SendQueuesMonitor();
    void add(Queue<T>* queue, const int& client_id);
    void send_to_client(const T& msg, const int& client_id);
    void broadcast(const std::list<T>& msgs);
    void broadcast(const T& msg);
    void remove_all();
};

// Implementation of SendQueuesMonitor methods
template <typename T>
SendQueuesMonitor<T>::SendQueuesMonitor(): m(), send_queues_map() {}

template <typename T>
void SendQueuesMonitor<T>::add(Queue<T>* queue, const int& client_id) {
    std::lock_guard<std::mutex> lock(m);
    send_queues_map[client_id] = queue;
}

template <typename T>
void SendQueuesMonitor<T>::remove_all() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& pair: send_queues_map) {
        delete pair.second;
    }
    send_queues_map.clear();
}

template <typename T>
void SendQueuesMonitor<T>::broadcast(const std::list<T>& msgs) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& pair: send_queues_map) {
        for (const T& msg: msgs) {
            pair.second->push(msg);
        }
    }
}

template <typename T>
void SendQueuesMonitor<T>::broadcast(const T& msg) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& pair: send_queues_map) {
        pair.second->push(msg);
    }
}

template <typename T>
void SendQueuesMonitor<T>::send_to_client(const T& msg, const int& client_id) {
    std::lock_guard<std::mutex> lock(m);
    send_queues_map[client_id]->push(msg);
}
#endif  // SEND_QUEUES_MONITOR_H
