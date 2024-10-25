#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

class CustomizedPlayerInfoMsg;
class ViewLobbiesMsg;
class ChooseLobbyMsg;
class CreateLobbyMsg;
class StartGameMsg;
class GoBackMsg;
class PickupDropItemMsg;
class StartMoveLeftMsg;
class StopMoveLeftMsg;
class StartMoveRightMsg;
class StopMoveRightMsg;
class JumpMsg;
class PlayDeadMsg;
class ShootMsg;

class ClientHandler {
public:
    virtual void handle(CustomizedPlayerInfoMsg& msg) = 0;
    virtual void handle(ViewLobbiesMsg& msg) = 0;
    virtual void handle(ChooseLobbyMsg& msg) = 0;
    virtual void handle(CreateLobbyMsg& msg) = 0;
    virtual void handle(StartGameMsg& msg) = 0;
    virtual void handle(GoBackMsg& msg) = 0;
    virtual void handle(PickupDropItemMsg& msg) = 0;
    virtual void handle(StartMoveLeftMsg& msg) = 0;
    virtual void handle(StopMoveLeftMsg& msg) = 0;
    virtual void handle(StartMoveRightMsg& msg) = 0;
    virtual void handle(StopMoveRightMsg& msg) = 0;
    virtual void handle(JumpMsg& msg) = 0;
    virtual void handle(PlayDeadMsg& msg) = 0;
    virtual void handle(ShootMsg& msg) = 0;
};


#endif // CLIENT_HANDLER_H
