#include <iostream>

#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "client.h"
#define MAX_SIZE 100

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    Queue<GenericMsg*> send_queue(MAX_SIZE);
    Queue<GenericMsg*> recv_queue(MAX_SIZE);

    Client client(argv[1], argv[2], send_queue, recv_queue);
    client.run();

    return 0;
}
