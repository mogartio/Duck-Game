#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

class ExampleMsg;
// class LobbyListMsg;
// class JoinedLobbyMsg;
// class ServerErrorMsg;
// class MapInfoMsg;
// class PlayerInfoMsg;
// class FinishGameMsg;
// class WinnerMsg;

class ServerHandler {
public:
    virtual void handle(ExampleMsg& msg) = 0;
    // virtual void handle(LobbyListMsg& msg) = 0;
    // virtual void handle(JoinedLobbyMsg& msg) = 0;
    // virtual void handle(ServerErrorMsg& msg) = 0;
    // virtual void handle(MapInfoMsg& msg) = 0;
    // virtual void handle(PlayerInfoMsg& msg) = 0;
    // virtual void handle(FinishGameMsg& msg) = 0;
    // virtual void handle(WinnerMsg& msg) = 0;

    virtual ~ServerHandler() = default;
};

#endif // SERVER_HANDLER_H
