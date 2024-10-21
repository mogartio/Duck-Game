#include "client.h"
#include <iostream>

int main(int argc, char const* argv[]) {

	if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

	const std::string hostname = argv[1];
	const std::string port = argv[2];

	Client client(hostname, port);

	return client.run();
}
