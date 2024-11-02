#include <iostream>

#include "../common/messages/generic_msg.h"
#include "../common/socket/socket.h"

#include "client_protocol.h"

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    std::cout << argv[1] << std::endl;

    Socket skt(argv[1], argv[2]);
    ClientProtocol protocol(skt);

    std::string input;

    StartActionMsg msg(ActionsId::MOVE_LEFT, "player1");
    protocol.send(&msg);
    ViewLobbiesMsg msg2;
    protocol.send(&msg2);

    GenericMsg* msg_recv1 = protocol.receive();
    std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg_recv1->get_header()) << std::endl;
    GenericMsg* msg_recv2 = protocol.receive();
    std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg_recv2->get_header()) << std::endl;

    return 0;
}
