#ifndef CLIENT_H
#define CLIENT_H

#include "../common/socket/socket.h"
#include "client_protocol.h"
#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "receiver.h"
#include "sender.h"

class Client {
private: 
    Socket skt;
    ClientProtocol protocol;
    Queue<GenericMsg*>& send_queue;
    Queue<GenericMsg*>& recv_queue;
    Receiver receiver;
    Sender sender;

public: 
    Client(const char* host, const char* port, Queue<GenericMsg*>& send_queue, Queue<GenericMsg*>& recv_queue);
    void run();
    void stop();

};



#endif // CLIENT_H
