/*
    Prototipo de protocol para fines practicos
    No sirve para nada mas que para probar que anda
    No le hice un .cpp por eso
*/

#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "../common/socket.h"

class Protocol {
protected:
    Socket skt;

public:
    Protocol(Socket& skt): skt(std::move(skt)) {}

    void sendString(const std::string& str) {
        bool was_closed = false;
        skt.sendall(str.c_str(), str.size(), &was_closed);
    }

    std::string receiveString() {
        bool was_closed = false;
        std::vector<char> buf(10);
        skt.recvall(buf.data(), 10, &was_closed);
        return std::string(buf.data(), buf.size());
    }
};

#endif
