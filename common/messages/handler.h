#ifndef HANDLER_H
#define HANDLER_H

class CustomizedPlayerInfoMsg;
class ViewLobbiesMsg;
class ChooseLobbyMsg;
class CreateLobbyMsg;
class GoBackMsg;
class ExitFromLobbyMsg;
class StartGameMsg;
class PickupDropMsg;
class MoveLeftMsg;
class MoveRightMsg;
class JumpMsg;
class PlayDeadMsg;
class ShootMsg;
class SendLobbiesListMsg;
class EverythingOkMsg;
class ErrorMsg;
class SendMapMsg;
class GameEndedMsg;
class WinnerMsg;

class Handler {
public:
    // from client
    virtual void handle_send(CustomizedPlayerInfoMsg& msg);
    virtual void handle_send(ViewLobbiesMsg& msg);
    virtual void handle_send(ChooseLobbyMsg& msg);
    virtual void handle_send(CreateLobbyMsg& msg);
    virtual void handle_send(GoBackMsg& msg);
    virtual void handle_send(ExitFromLobbyMsg& msg);
    virtual void handle_send(StartGameMsg& msg);
    // in-game commands
    virtual void handle_send(PickupDropMsg& msg);
    virtual void handle_send(MoveLeftMsg& msg);
    virtual void handle_send(MoveRightMsg& msg);
    virtual void handle_send(JumpMsg& msg);
    virtual void handle_send(PlayDeadMsg& msg);
    virtual void handle_send(ShootMsg& msg);
    // from server
    virtual void handle_send(SendLobbiesListMsg& msg);
    virtual void handle_send(EverythingOkMsg& msg);
    virtual void handle_send(ErrorMsg& msg);
    virtual void handle_send(SendMapMsg& msg);
    virtual void handle_send(GameEndedMsg& msg);
    virtual void handle_send(WinnerMsg& msg);
    // in-game from server
    // ... 

    // from client 
    virtual void handle_recv(CustomizedPlayerInfoMsg& msg);
    virtual void handle_recv(ViewLobbiesMsg& msg);
    virtual void handle_recv(ChooseLobbyMsg& msg);
    virtual void handle_recv(CreateLobbyMsg& msg);
    virtual void handle_recv(GoBackMsg& msg);
    virtual void handle_recv(ExitFromLobbyMsg& msg);
    virtual void handle_recv(StartGameMsg& msg);
    // in-game commands
    virtual void handle_recv(PickupDropMsg& msg);
    virtual void handle_recv(MoveLeftMsg& msg);
    virtual void handle_recv(MoveRightMsg& msg);
    virtual void handle_recv(JumpMsg& msg);
    virtual void handle_recv(PlayDeadMsg& msg);
    virtual void handle_recv(ShootMsg& msg);
    // from server
    virtual void handle_recv(SendLobbiesListMsg& msg);
    virtual void handle_recv(EverythingOkMsg& msg);
    virtual void handle_recv(ErrorMsg& msg);
    virtual void handle_recv(SendMapMsg& msg);
    virtual void handle_recv(GameEndedMsg& msg);
    virtual void handle_recv(WinnerMsg& msg);
    // in-game from server


    virtual ~Handler() = default;
};

#endif 
