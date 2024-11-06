#include <iomanip>  // Incluir el encabezado <iomanip> para std::setw y std::setfill
#include <iostream>
#include <list>
#include <sstream>  // Incluir el encabezado <sstream>

#include "../common/messages/generic_msg.h"
#include "../common/queue.h"
#include "SDL/game/frontOnePlaye.h"

#include "client.h"
#define MAX 1000

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    Queue<GenericMsg*> send_queue(MAX);
    Queue<GenericMsg*> recv_queue(MAX);

    Client client1(argv[1], argv[2], &send_queue, &recv_queue);
    // Client client2(argv[1], argv[2], &send_queue, &recv_queue);

    CreateLobbyMsg* msg2 = new CreateLobbyMsg("pepito");
    send_queue.push(msg2);

    StartGameMsg msg3;
    send_queue.push(&msg3);

    for (int i = 0; i < 2; i++) {
        GenericMsg* msg = recv_queue.pop();
        std::cout << "recibi header: " << int(msg->get_header()) << std::endl;
    }

    OnePlayer front(send_queue, recv_queue, "pepito");
    front.play();

    recv_queue.close();
    client1.stop();
    return 0;
}
