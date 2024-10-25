#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg<ServerHandler>*>* recv_queue, Protocol<ServerHandler>* protocol):
        recv_queue(recv_queue), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            GenericMsg<ServerHandler>* msg = protocol->receive();
            recv_queue->push(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }

void Receiver::update_recv_queue(Queue<GenericMsg<ServerHandler>*>* new_recv_queue) {
    recv_queue = new_recv_queue;
}

void Receiver::update_protocol(Protocol<ServerHandler>* new_protocol) {
    protocol = new_protocol;
}