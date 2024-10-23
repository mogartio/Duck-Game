#include "../common/receiver.h"

Receiver::Receiver(Queue<std::string>& recv_queue, Protocol& protocol):
        recv_queue(recv_queue), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            std::string msg = protocol.receiveString();
            recv_queue.push(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }
