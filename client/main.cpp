#include "common/foo.h"
#include "protocol.h"
#include "common/socket.h"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <host> <puerto>\n";
        return 1;
    }
    Socket skt(argv[1], argv[2]);
    Protocol protocol(skt);

    while(true) {
        std::string input;
        std::cout << "Ingrese un mensaje: ";
        std::getline(std::cin, input);
        protocol.sendString(input);
        
        std::string str = protocol.receiveString();
        std::cout << "\nReceived: " << str << std::endl; 
    }
    return 0;
	
}