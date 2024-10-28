#include <iostream>

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

    while (input != "q") {
        std::cin >> input;

        if (input == "1") {
            std::cout << "Insert a color: ";
            int color;
            std::cin >> color;
            std::cout << "Insert a player name: ";
            std::string player_name;
            std::cin >> player_name;
            CustomizedPlayerInfoMsg msg(color, player_name);
            protocol.send(&msg);
            std::cout << "Sent message" << std::endl;
        } else if (input == "2") {
            ViewLobbiesMsg msg = ViewLobbiesMsg();
            protocol.send(&msg);
            std::cout << "Sent message" << std::endl;
        } else if (input == "3") {
            std::cout << "Insert a lobby id: ";
            int lobby_id;
            std::cin >> lobby_id;
            ChooseLobbyMsg msg = ChooseLobbyMsg(lobby_id);
            protocol.send(&msg);
            std::cout << "Sent message" << std::endl;
        }
        GenericMsg* msg = protocol.receive();
        if (msg != nullptr) {
            msg->print_info();
        }
    }

    return 0;
}
