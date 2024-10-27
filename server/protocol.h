#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../common/protocolo-common.h"

class Protocol: public ProtocoloCommon {
public:
    explicit Protocol(Socket& socket): ProtocoloCommon(socket) {}
};
#endif
