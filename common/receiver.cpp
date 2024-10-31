#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol):
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

