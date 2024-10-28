#include "sender.h"

Sender::Sender(Queue<GenericMsg*>* send_queue, ServerProtocol* protocol):
        send_queue(send_queue), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            GenericMsg* msg = send_queue->pop();
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

void Sender::update_send_queue(Queue<GenericMsg*>* new_send_queue) { send_queue = new_send_queue; }

void Sender::update_protocol(ServerProtocol* new_protocol) { protocol = new_protocol; }
