#include <string>
#include <cstdint>
#include <iostream>
#include "mensaje-lobby.h"

struct ClientInfo {
    virtual ~ClientInfo() = default;
    virtual uint8_t getHeader() const = 0;
};

struct CustomizePlayer : public ClientInfo {
    uint8_t header = 0x01;
    uint16_t nameLength;
    std::string name;
    uint8_t color;
    bool askingColors;

    CustomizePlayer(bool askingColors, const std::string& name, uint8_t color)
        : nameLength(name.size()), name(name), color(color), askingColors(askingColors) {}

    uint8_t getHeader() const override { return header; }
};

struct KeyboardAction : public ClientInfo {
    uint8_t header = 0x03;
    uint8_t action;
    uint8_t type;

    KeyboardAction(uint8_t action, uint8_t type = 0) : action(action), type(type) {}

    uint8_t getHeader() const override { return header; }
};


