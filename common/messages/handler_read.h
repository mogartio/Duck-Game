#ifndef HANDLER_READ_H
#define HANDLER_READ_H

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

class HandlerReader {
public:
    // reader methods game
    virtual void handle_read(const PickupDropMsg& msg);
    virtual void handle_read(const StartActionMsg& msg);
    virtual void handle_read(const StopActionMsg& msg);

    virtual ~HandlerReader() = default;
};

#endif
