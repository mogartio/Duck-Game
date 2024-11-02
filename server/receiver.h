#ifndef RECEIVER_H
#define RECEIVER_H
#include <array>
#include <string>

#include "../common/queue.h"
#include "../common/thread.h"

#include "client.h"
#include "protocolo-common.h"

#define RECEIVER_LOBBY 0
#define RECEIVER_GAME 1
#define SPACE_ARRAY 2

class Receiver: public Thread {
private:
    Queue<GenericMsg*>* recv_queue_game;
    ProtocoloCommon* protocol;
    Client* client;

    void run() override;

public:
    explicit Receiver(Queue<GenericMsg*>* recv_queue_game, ProtocoloCommon* protocol,
                      Client* client);

    /*
     * Detiene la ejecución del hilo seteando _keep_running en false.
     */
    void kill();
};
#endif  // RECEIVER_H
