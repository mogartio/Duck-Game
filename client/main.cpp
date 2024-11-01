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

    GenericMsg* rmsg1 = recv_queue.pop();
    std::cout  << "Recibi en el client: 0x" << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(rmsg1->get_header())<< std::endl;
    GenericMsg* rmsg2 = recv_queue.pop();
    std::cout  << "Recibi en el client: 0x" << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(rmsg2->get_header())<< std::endl;
    // GenericMsg* rmsg3 = recv_queue.pop();
    // std::cout  << "Recibi en el client: 0x" << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(rmsg3->get_header())<< std::endl;

    OnePlayer front(send_queue, recv_queue, "pablito");
    front.play();

    // if (rmsg3->get_header() == GenericMsg::MsgTypeHeader::SEND_MAP_MSG) {
    //     SendMapMsg* map = dynamic_cast<SendMapMsg*>(rmsg3);
    //     std::vector<uint16_t> mapa = map->get_map();
    //     for (size_t i = 0; i < mapa.size(); i++) {
    //         std::cout << mapa[i] << " ";
    //         if ((i+1) % 8 == 0) {
    //             std::cout << std::endl;
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    recv_queue.close();
    client.stop();

    return 0;
}
