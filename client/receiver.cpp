#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg*>* recv_queue, ClientProtocol* protocol):
        recv_queue(recv_queue), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            GenericMsg* msg = protocol->receive();
            recv_queue->push(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }

void Receiver::update_recv_queue(Queue<GenericMsg*>* new_recv_queue) {
    recv_queue = new_recv_queue;
}

void Receiver::update_protocol(ClientProtocol* new_protocol) { protocol = new_protocol; }
