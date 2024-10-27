#ifndef SOCKETERROR_H
#define SOCKETERROR_H

#include <stdexcept>
#include <string>

class SocketClosedError: public std::runtime_error {
public:
    // Constructor que recibe que es lo que se intentaba hacer cuando se cerro el socket
    explicit SocketClosedError(const char type_operation[]):
            std::runtime_error("Socket trying to " + std::string(type_operation) +
                               " but this was close") {}
};
#endif
