#include "sender.h"

Sender::Sender(Queue<GenericMsg*>* send_queue, Socket& skt): send_queue(send_queue), skt(skt) {}

void Sender::run() {
    assingProtocol();
    while (_keep_running) {
        try {
            GenericMsg* msg = send_queue->pop();
            protocol->send(msg);
            delete msg;
            msg = nullptr;
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Sender::kill() {
    send_queue->close();
    _keep_running = false;
}
