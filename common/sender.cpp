#include "sender.h"

Sender::Sender(Queue<std::shared_ptr<GenericMsg>>* send_queue, ProtocoloCommon* protocol):
        send_queue(send_queue), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            std::shared_ptr<GenericMsg> msg = send_queue->pop();
            execute(msg);
            protocol->send(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Sender::kill() {
    send_queue->close();
    _keep_running = false;
}

void Sender::execute(std::shared_ptr<GenericMsg> msg) { (void)msg; }
