#ifndef HANDLER_SENDER_H
#define HANDLER_SENDER_H

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

class HandlerSender {
public:
    // from client
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg);
    virtual void handle_send(const ViewLobbiesMsg& msg);
    virtual void handle_send(const ChooseLobbyMsg& msg);
    virtual void handle_send(const CreateLobbyMsg& msg);
    virtual void handle_send(const GoBackMsg& msg);
    virtual void handle_send(const ExitFromLobbyMsg& msg);
    virtual void handle_send(const StartGameMsg& msg);
    // in-game commands
    virtual void handle_send(const PickupDropMsg& msg);
    virtual void handle_send(const StartActionMsg& msg);
    virtual void handle_send(const StopActionMsg& msg);
    // from server
    virtual void handle_send(const SendLobbiesListMsg& msg);
    virtual void handle_send(const EverythingOkMsg& msg);
    virtual void handle_send(const ErrorMsg& msg);
    virtual void handle_send(const SendMapMsg& msg);
    virtual void handle_send(const GameEndedMsg& msg);
    virtual void handle_send(const WinnerMsg& msg);
    // in-game from server
    virtual void handle_send(const UpdatedPlayerInfoMsg& msg);
    virtual void handle_send(const ProjectileInfoMsg& msg);

    virtual ~HandlerSender() = default;
};

#endif