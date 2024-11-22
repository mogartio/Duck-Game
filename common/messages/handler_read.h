#ifndef HANDLER_READ_H
#define HANDLER_READ_H

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

class HandlerReader {
public:
    // reader methods menu
    virtual void handle_read(const InfoLobbyMsg& msg);
    virtual void handle_read(const CustomizedPlayerInfoMsg& msg);
    virtual void handle_read(const ViewLobbiesMsg& msg);
    virtual void handle_read(const ChooseLobbyMsg& msg);
    virtual void handle_read(const CreateLobbyMsg& msg);
    virtual void handle_read(const GoBackMsg& msg);
    virtual void handle_read(const ExitFromLobbyMsg& msg);
    virtual void handle_read(const StartGameMsg& msg);
    virtual void handle_read(const PlayerInfoMsg& msg);
    // reader methods game
    virtual void handle_read(const PickupDropMsg& msg);
    virtual void handle_read(const StartActionMsg& msg);
    virtual void handle_read(const StopActionMsg& msg);
    // reader methods info from client
    virtual void handle_read(const SendLobbiesListMsg& msg);
    virtual void handle_read(const EverythingOkMsg& msg);
    virtual void handle_read(const ErrorMsg& msg);
    virtual void handle_read(const SendMapMsg& msg);
    virtual void handle_read(const GameEndedMsg& msg);
    virtual void handle_read(const WinnerMsg& msg);
    // in-game from server
    virtual void handle_read(const UpdatedPlayerInfoMsg& msg);
    virtual void handle_read(const ProjectileInfoMsg& msg);
    virtual void handle_read(const NotProyectileInfo& msg);
    virtual void handle_read(const ShootMsg& msg);

    virtual ~HandlerReader() = default;
};

#endif
