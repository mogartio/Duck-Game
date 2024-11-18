#include "sender.h"

Sender::Sender(Queue<std::shared_ptr<GenericMsg>>* send_queue, ProtocoloCommon* protocol):
        send_queue(send_queue), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            std::shared_ptr<GenericMsg> msg = send_queue->pop();
            // std::cout << "SENT MSG: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msg->get_header()) << std::endl;
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
