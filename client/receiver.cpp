#include "receiver.h"

ReceiverClient::ReceiverClient(Queue<GenericMsg*>* recv_queue, ProtocoloCommon* protocol):
        Receiver(recv_queue, protocol) {}

void ReceiverClient::executeMsg(GenericMsg* msg) { recv_queue->push(msg); }
