#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "queue.h"
#include "thread.h"

#include "../server/protocol.h"

class Sender: public Thread {
private:
    Queue<std::string>& send_queue;
    Protocol& protocol;

    void run() override;

public:
    Sender(Queue<std::string>& send_queue, Protocol& protocol);
    void kill();
};
#endif  // SENDER_H
