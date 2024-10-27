#ifndef HANDLE_H
#define HANDLE_H

class EverythingOkey;
class SomethingWrong;
class ExampleMsg;
class ViewLobbiesMsg;
class LobbyListMsg;
class JoinedLobbyMsg;
class CreateLobbyMsg;
class ExitMsg;
class StartGameMsg;
class CustomizedPlayerInfoMsg;
class MapInfoMsg;
class PickupDropItemMsg;
class StartMoveLeftMsg;
class StopMoveLeftMsg;
class StartMoveRightMsg;
class StopMoveRightMsg;
class JumpMsg;
class PlayDeadMsg;
class ShootMsg;
class PlayerInfoMsg;
class FinishGameMsg;
class WinnerMsg;


class Handler {
public:
    // SEND
    // Response server
    virtual void handle_send(const EverythingOkey& msg);
    virtual void handle_send(const SomethingWrong& msg);

    // Lobby messages
    virtual void handle_send(const ExampleMsg& msg);
    virtual void handle_send(const ViewLobbiesMsg& msg);
    virtual void handle_send(const LobbyListMsg& msg);
    virtual void handle_send(const JoinedLobbyMsg& msg);
    virtual void handle_send(const CreateLobbyMsg& msg);
    virtual void handle_send(const ExitMsg& msg);
    virtual void handle_send(const StartGameMsg& msg);

    // Customized messages
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg);
    virtual void handle_send(const MapInfoMsg& msg);

    // Game messages
    virtual void handle_send(const PickupDropItemMsg& msg);
    virtual void handle_send(const StartMoveLeftMsg& msg);
    virtual void handle_send(const StopMoveLeftMsg& msg);
    virtual void handle_send(const StartMoveRightMsg& msg);
    virtual void handle_send(const StopMoveRightMsg& msg);
    virtual void handle_send(const JumpMsg& msg);
    virtual void handle_send(const PlayDeadMsg& msg);
    virtual void handle_send(const ShootMsg& msg);
    virtual void handle_send(const PlayerInfoMsg& msg);
    virtual void handle_send(const FinishGameMsg& msg);
    virtual void handle_send(const WinnerMsg& msg);

    // RECV
    // Response server
    virtual void handle_recv(const EverythingOkey* msg);
    virtual void handle_recv(const SomethingWrong* msg);

    // Lobby messages
    virtual void handle_recv(const ExampleMsg* msg);
    virtual void handle_recv(const ViewLobbiesMsg* msg);
    virtual void handle_recv(const LobbyListMsg* msg);
    virtual void handle_recv(const JoinedLobbyMsg* msg);
    virtual void handle_recv(const CreateLobbyMsg* msg);
    virtual void handle_recv(const ExitMsg* msg);
    virtual void handle_recv(const StartGameMsg* msg);

    // Customized messages
    virtual void handle_recv(const CustomizedPlayerInfoMsg* msg);
    virtual void handle_recv(const MapInfoMsg* msg);

    // Game messages
    virtual void handle_recv(const PickupDropItemMsg* msg);
    virtual void handle_recv(const StartMoveLeftMsg* msg);
    virtual void handle_recv(const StopMoveLeftMsg* msg);
    virtual void handle_recv(const StartMoveRightMsg* msg);
    virtual void handle_recv(const StopMoveRightMsg* msg);
    virtual void handle_recv(const JumpMsg* msg);
    virtual void handle_recv(const PlayDeadMsg* msg);
    virtual void handle_recv(const ShootMsg* msg);
    virtual void handle_recv(const PlayerInfoMsg* msg);
    virtual void handle_recv(const FinishGameMsg* msg);
    virtual void handle_recv(const WinnerMsg* msg);

    virtual ~Handler() = default;
};

#endif  // HANDLE_H
