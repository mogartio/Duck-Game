#include "receiver.h"

ReceiverClient::ReceiverClient(Queue<GenericMsg*>* recv_queue, Socket& skt):
        Receiver(recv_queue, skt) {}

void ReceiverClient::executeMsg(GenericMsg* msg) { recv_queue->push(msg); }

void ReceiverClient::assingProtocol() { protocol = new ClientProtocol(skt); }
