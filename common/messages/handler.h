#ifndef HANDLE_H
#define HANDLE_H


class Handler {
public:
    // SEND
    // Response server
    virtual void handle_send(const EverythingOkey& msg) { (void)msg; }
    virtual void handle_send(const SomethingWrong& msg) { (void)msg; }

    // Lobby messages
    virtual void handle_send(const ExampleMsg& msg) { (void)msg; }
    virtual void handle_send(const ViewLobbiesMsg& msg) { (void)msg; }
    virtual void handle_send(const LobbyListMsg& msg) { (void)msg; }
    virtual void handle_send(const JoinedLobbyMsg& msg) { (void)msg; }
    virtual void handle_send(const CreateLobbyMsg& msg) { (void)msg; }
    virtual void handle_send(const ExitMsg& msg) { (void)msg; }
    virtual void handle_send(const StartGameMsg& msg) { (void)msg; }

    // Customized messages
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg) { (void)msg; }
    virtual void handle_send(const MapInfoMsg& msg) { (void)msg; }

    // Game messages
    virtual void handle_send(const PickupDropItemMsg& msg) { (void)msg; }
    virtual void handle_send(const StartMoveLeftMsg& msg) { (void)msg; }
    virtual void handle_send(const StopMoveLeftMsg& msg) { (void)msg; }
    virtual void handle_send(const StartMoveRightMsg& msg) { (void)msg; }
    virtual void handle_send(const StopMoveRightMsg& msg) { (void)msg; }
    virtual void handle_send(const JumpMsg& msg) { (void)msg; }
    virtual void handle_send(const PlayDeadMsg& msg) { (void)msg; }
    virtual void handle_send(const ShootMsg& msg) { (void)msg; }
    virtual void handle_send(const PlayerInfoMsg& msg) { (void)msg; }
    virtual void handle_send(const FinishGameMsg& msg) { (void)msg; }
    virtual void handle_send(const WinnerMsg& msg) { (void)msg; }

    // RECV
    // Response server
    virtual void handle_recv(EverythingOkey** msg) { (void)msg; }
    virtual void handle_recv(SomethingWrong** msg) { (void)msg; }

    // Lobby messages
    virtual void handle_recv(ExampleMsg** msg) { (void)msg; }
    virtual void handle_recv(ViewLobbiesMsg** msg) { (void)msg; }
    virtual void handle_recv(LobbyListMsg** msg) { (void)msg; }
    virtual void handle_recv(JoinedLobbyMsg** msg) { (void)msg; }
    virtual void handle_recv(CreateLobbyMsg** msg) { (void)msg; }
    virtual void handle_recv(ExitMsg** msg) { (void)msg; }
    virtual void handle_recv(StartGameMsg** msg) { (void)msg; }

    // Customized messages
    virtual void handle_recv(CustomizedPlayerInfoMsg** msg) { (void)msg; }
    virtual void handle_recv(MapInfoMsg** msg) { (void)msg; }

    // Game messages
    virtual void handle_recv(PickupDropItemMsg** msg) { (void)msg; }
    virtual void handle_recv(StartMoveLeftMsg** msg) { (void)msg; }
    virtual void handle_recv(StopMoveLeftMsg** msg) { (void)msg; }
    virtual void handle_recv(StartMoveRightMsg** msg) { (void)msg; }
    virtual void handle_recv(StopMoveRightMsg** msg) { (void)msg; }
    virtual void handle_recv(JumpMsg** msg) { (void)msg; }
    virtual void handle_recv(PlayDeadMsg** msg) { (void)msg; }
    virtual void handle_recv(ShootMsg** msg) { (void)msg; }
    virtual void handle_recv(PlayerInfoMsg** msg) { (void)msg; }
    virtual void handle_recv(FinishGameMsg** msg) { (void)msg; }
    virtual void handle_recv(WinnerMsg** msg) { (void)msg; }

    virtual ~Handler() = default;
};

#endif  // HANDLE_H
