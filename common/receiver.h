#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "queue.h"
#include "socket/socket.h"
#include "thread.h"

#include "../server/protocol.h"

class Receiver: public Thread {
private:
    Queue<std::string>& recv_queue;
    Protocol& protocol;

    void run() override;

public:
    explicit Receiver(Queue<std::string>& recv_queue, Protocol& protocol);
    void kill();
};
#endif  // RECEIVER_H
