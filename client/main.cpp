#include <iostream>

#include "../common/socket/socket.h"
#include "client_protocol.h"
#include "../common/messages/generic_msg.h"
#include "../common/queue.h"
#include "client.h"
#include "SDL/game/frontOnePlaye.h"
#include <list>
#define MAX 1000

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    Queue<GenericMsg*> send_queue(MAX);
    Queue<GenericMsg*> recv_queue(MAX);
    
    Client client(argv[1], argv[2], &send_queue, &recv_queue);

    ViewLobbiesMsg msg1;
    send_queue.push(&msg1);
    
    OnePlayer front(send_queue, recv_queue, "juancito");
    front.play();

    recv_queue.close();
    client.stop();

    return 0;
}
