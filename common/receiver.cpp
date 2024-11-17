#include "receiver.h"

Receiver::Receiver(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol):
        recv_queue(recv_queue), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            GenericMsg* msg = protocol->receive();
            // std::cout << "RECEIVED MSG: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msg->get_header()) << std::endl;
            executeMsg(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }
