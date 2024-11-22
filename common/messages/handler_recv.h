#ifndef HANDLER_RECEIVER_H
#define HANDLER_RECEIVER_H

class InfoLobbyMsg;
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
class PlayerInfoMsg;
class NotProyectileInfo;
class ShootMsg;
// TODO: esto se puede mejorar lanzando mensajes de errores si no se implementan los metodos
// TODO: en las clases hijas ya que hasta ahora solo haciamos (void)msg

class HandlerReceiver {
public:
    // from client
    virtual void handle_recv(InfoLobbyMsg& msg);
    virtual void handle_recv(CustomizedPlayerInfoMsg& msg);
    virtual void handle_recv(ViewLobbiesMsg& msg);
    virtual void handle_recv(ChooseLobbyMsg& msg);
    virtual void handle_recv(CreateLobbyMsg& msg);
    virtual void handle_recv(GoBackMsg& msg);
    virtual void handle_recv(ExitFromLobbyMsg& msg);
    virtual void handle_recv(StartGameMsg& msg);
    virtual void handle_recv(PlayerInfoMsg& msg);
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
    virtual void handle_recv(NotProyectileInfo& msg);
    virtual void handle_recv(ShootMsg& msg);

    virtual ~HandlerReceiver() = default;
};

#endif
