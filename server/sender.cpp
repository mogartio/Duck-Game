#include "sender.h"

Sender::Sender(Queue<std::string>& send_queue, Protocol& protocol):
        send_queue(send_queue), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            std::string msg = send_queue.pop();
            protocol.sendString(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Sender::kill() {
    send_queue.close();
    _keep_running = false;
}