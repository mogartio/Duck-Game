#include <iostream>

#include "../common/protocol/send.h"

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }
    Socket skt(argv[1], argv[2]);
    // Protocol<ServerHandler> protocol(skt);

    std::string input;
    while (input != "q") {
        // std::getline(std::cin, input);
        // uint16_t input_size = static_cast<uint16_t>(input.size());

        // protocol.send_uint16_t(input_size);
        // protocol.send_string(input);

        // std::cout << "Sent: " << input << std::endl;

        // std::string msg = protocol.recv_string(input_size);
        // std::cout << "Received: " << msg << std::endl;
    }

    return 0;
}
