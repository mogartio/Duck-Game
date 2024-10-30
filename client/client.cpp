#include "client.h"
#include "client.h"

Client::Client(const char* host, const char* port, Queue<GenericMsg*>& send_queue, Queue<GenericMsg*>& recv_queue)
    : skt(host, port), protocol(skt), send_queue(send_queue), recv_queue(recv_queue),
      receiver(&recv_queue, &protocol), sender(&send_queue, &protocol) {}

void Client::run() {
    receiver.start();
    sender.start();
}

void Client::stop() {
    receiver.stop();
    sender.stop();
}