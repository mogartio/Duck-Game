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
    }

    return 0;
}
