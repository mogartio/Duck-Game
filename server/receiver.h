#ifndef RECEIVER_H
#define RECEIVER_H

#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "protocol.h"

class Receiver : public Thread {
private:
    Queue<std::string>& recv_queue;
    Protocol& protocol;

    void run() override;
public:
    explicit Receiver(Queue<std::string>& recv_queue, Protocol& protocol);
    void kill();

};

#endif  // RECEIVER_H
