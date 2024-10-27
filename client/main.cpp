#include <iostream>

#include "client_protocol.h"

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    Socket skt(argv[1], argv[2]);
    ClientProtocol protocol(skt);

    std::string input;

    /* HAY QUE HACER ESTA MISMA PRUEBA CON ALGUN OTRO MENSAJE QUE ESTE DEFINIDO
    while (input != "q") {
        std::cin >> input;
        if (input == "1") {
            ClientExampleMsg1 msg("Hello world");
            protocol.send(&msg);
            std::cout << "Sent message: " << "Hello world" << std::endl;
        } else if (input == "2") {
            ClientExampleMsg2 msg(42);
            protocol.send(&msg);
            std::cout << "Sent message: " << 42 << std::endl;
        }
        GenericMsg* msg = protocol.receive();
        msg->print_data();
    }
    */

    return 0;
}
