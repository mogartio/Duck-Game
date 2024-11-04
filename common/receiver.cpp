#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg*>* recv_queue, Socket& skt): recv_queue(recv_queue), skt(skt) {}

void Receiver::run() {
    assingProtocol();
    while (_keep_running) {
        try {
            GenericMsg* msg = protocol->receive();
            executeMsg(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }
