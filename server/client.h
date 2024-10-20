#ifndef CLIENT_H
#define CLIENT_H

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protocol.h"
#include "receiver.h"
#include "sender.h"

class Client {
private:
    Socket client_skt;
    Queue<std::string>& send_queue;
    Queue<std::string>& recv_queue;
    int id;  // a chequear, para la funcionalidad futura
    Protocol protocol;
    Receiver receiver;
    Sender sender;

    void start_client();

public:
    Client(Socket&& client_skt, Queue<std::string>& send_queue, Queue<std::string>& recv_queue,
           int id);
    bool operator==(const Client& other) const;

    void stop();
    bool is_alive();
};

#endif  // CLIENT_H
