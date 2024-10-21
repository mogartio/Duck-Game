#include <string>
#include <cstdint>
#include <iostream>

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

//LobbyAction (uint8 action, uint8 lobbyNumbre, uint8 playerCount)
struct LobbyAction : public ClientInfo {
    uint8_t header = 0x02;
    uint8_t action;
    uint8_t lobbyNumber;
    uint8_t playerCount;

    LobbyAction(uint8_t action, uint8_t lobbyNumber = 0, uint8_t playerCount = 0)
        : action(action), lobbyNumber(lobbyNumber), playerCount(playerCount) {}

    uint8_t getHeader() const override { return header; }
};

struct KeyboardAction : public ClientInfo {
    uint8_t header = 0x03;
    uint8_t action;
    uint8_t type;

    KeyboardAction(uint8_t action, uint8_t type = 0) : action(action), type(type) {}

    uint8_t getHeader() const override { return header; }
};


