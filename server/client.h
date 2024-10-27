#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <utility>

#include "../common/queue.h"
#include "../common/socket/socket.h"
#include "../common/thread.h"
#include "../common/messages/handler.h"

#include "receiver.h"
#include "sender.h"
#include "server_protocol.h"

class Client {
private:
    Socket client_skt;
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue;
    int id;  // a chequear, para la funcionalidad futura
    ServerProtocol protocol;
    Receiver receiver;
    Sender sender;

    void start_client();

public:
    Client(Socket&& client_skt, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue,
           int id);
    bool operator==(const Client* other) const;

    void stop();
    bool is_alive();
};

#endif  // CLIENT_H
