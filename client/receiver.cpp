#include "receiver.h"

ReceiverClient::ReceiverClient(Queue<std::shared_ptr<GenericMsg>>* recv_queue, ProtocoloCommon* protocol):
        Receiver(recv_queue, protocol) {}

void ReceiverClient::executeMsg(std::shared_ptr<GenericMsg> msg) { recv_queue->push(msg); }
