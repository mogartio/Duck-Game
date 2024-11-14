#include "sender.h"

Sender::Sender(Queue<GenericMsg*>* send_queue, ProtocoloCommon* protocol):
        send_queue(send_queue), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            GenericMsg* msg = send_queue->pop();
            if (msg->get_header() == 0x08) {
                std::cout << "El maldito mensaje pickup llego al sender" << std::endl;
            }
            protocol->send(msg);
            // delete msg;
            // msg = nullptr;
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Sender::kill() {
    send_queue->close();
    _keep_running = false;
}
