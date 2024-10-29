#ifndef HANDLER_RECEIVER_H
#define HANDLER_RECEIVER_H

class CustomizedPlayerInfoMsg;
class ViewLobbiesMsg;
class ChooseLobbyMsg;
class CreateLobbyMsg;
class GoBackMsg;
class ExitFromLobbyMsg;
class StartGameMsg;
class PickupDropMsg;
class StartActionMsg;
class StopActionMsg;
class SendLobbiesListMsg;
class EverythingOkMsg;
class ErrorMsg;
class SendMapMsg;
class GameEndedMsg;
class WinnerMsg;
class UpdatedPlayerInfoMsg;
class ProjectileInfoMsg;

class HandlerReceiver {
public:
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
    virtual void handle_recv(StartActionMsg& msg);
    virtual void handle_recv(StopActionMsg& msg);
    // from server
    virtual void handle_recv(SendLobbiesListMsg& msg);
    virtual void handle_recv(EverythingOkMsg& msg);
    virtual void handle_recv(ErrorMsg& msg);
    virtual void handle_recv(SendMapMsg& msg);
    virtual void handle_recv(GameEndedMsg& msg);
    virtual void handle_recv(WinnerMsg& msg);
    // in-game from server
    virtual void handle_recv(UpdatedPlayerInfoMsg& msg);
    virtual void handle_recv(ProjectileInfoMsg& msg);
   
    virtual ~HandlerReceiver() = default;
};

#endif
