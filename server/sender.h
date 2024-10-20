#ifndef SENDER_H
#define SENDER_H

#include "../common/thread.h"
#include "../common/queue.h"
#include "protocol.h"

class Sender : public Thread {
private:
    Queue<std::string>& send_queue;
    Protocol& protocol;

    void run() override;
public:
    Sender(Queue<std::string>& send_queue, Protocol& protocol);
    void kill();

};

#endif  // SENDER_H