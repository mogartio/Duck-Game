#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <utility>

#include "../common/receiver.h"

#include "client_protocol.h"
#include "receiver.h"
#include "sender.h"

class Client {
private:
    Socket client_skt;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    ClientProtocol protocol;
    ReceiverClient receiver;
    SenderClient sender;

    void start_client();

public:
    Client(const char* host, const char* port, Queue<GenericMsg*>* send_queue,
           Queue<GenericMsg*>* recv_queue);

    void stop();
    bool is_alive();
};

#endif  // CLIENT_H
