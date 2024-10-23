#include "../common/receiver.h"

Receiver::Receiver(Queue<std::string>* recv_queue, Protocol* protocol):
        recv_queue(recv_queue), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            // std::string msg = protocol.receiveString();
            // recv_queue.push(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }

void Receiver::update_recv_queue(Queue<std::string>* new_recv_queue) {
    recv_queue = new_recv_queue;
}

void Receiver::update_protocol(Protocol* new_protocol) {
    protocol = new_protocol;
}