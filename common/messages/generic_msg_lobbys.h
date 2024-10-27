#ifndef GENERIC_MSG_LOBBYS_H
#define GENERIC_MSG_LOBBYS_H

#include <string>

#include "generic_msg.h"

class LobbyMsg: public GenericMsg {
protected:
    enum lobbyType : uint8_t {
        EXAMPLE = 0x00,
        VIEW_LOBBIES = 0x01,
        LOBBY_LIST = 0x02,
        JOINED_LOBBY = 0x03,
        CREATE_LOBBY = 0x04,
        EXIT_FROM_LOBBY = 0x05,
        START_GAME = 0x06,
    };

private:
    lobbyType second_header;

public:
    explicit LobbyMsg(lobbyType second_header);

    virtual uint8_t get_second_header() const override;
};

class ExampleMsg: public LobbyMsg {
private:
    std::string data;

public:
    explicit ExampleMsg(std::string& data);

    std::string getData() const;

    virtual void accept_send(SendProtocol& protocol) override;
};

class ViewLobbiesMsg: public LobbyMsg {
public:
    ViewLobbiesMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class LobbyListMsg: public LobbyMsg {
public:
    LobbyListMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class JoinedLobbyMsg: public LobbyMsg {
public:
    JoinedLobbyMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class CreateLobbyMsg: public LobbyMsg {
public:
    CreateLobbyMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class ExitMsg: public LobbyMsg {
public:
    ExitMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};

class StartGameMsg: public LobbyMsg {
public:
    StartGameMsg();
    virtual void accept_send(SendProtocol& protocol) override;
};
#endif  // GENERIC_MSG_LOBBYS_H
