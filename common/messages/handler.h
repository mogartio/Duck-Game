#ifndef HANDLE_H
#define HANDLE_H

#include "generic_msg_customizer.h"
#include "generic_msg_game.h"
#include "generic_msg_lobbys.h"
#include "generic_msg_responseser.h"

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
    virtual void handle_recv(EverythingOkey* msg);
    virtual void handle_recv(SomethingWrong* msg);

    // Lobby messages
    virtual void handle_recv(ExampleMsg* msg);
    virtual void handle_recv(ViewLobbiesMsg* msg);
    virtual void handle_recv(LobbyListMsg* msg);
    virtual void handle_recv(JoinedLobbyMsg* msg);
    virtual void handle_recv(CreateLobbyMsg* msg);
    virtual void handle_recv(ExitMsg* msg);
    virtual void handle_recv(StartGameMsg* msg);

    // Customized messages
    virtual void handle_recv(CustomizedPlayerInfoMsg* msg);
    virtual void handle_recv(MapInfoMsg* msg);

    // Game messages
    virtual void handle_recv(PickupDropItemMsg* msg);
    virtual void handle_recv(StartMoveLeftMsg* msg);
    virtual void handle_recv(StopMoveLeftMsg* msg);
    virtual void handle_recv(StartMoveRightMsg* msg);
    virtual void handle_recv(StopMoveRightMsg* msg);
    virtual void handle_recv(JumpMsg* msg);
    virtual void handle_recv(PlayDeadMsg* msg);
    virtual void handle_recv(ShootMsg* msg);
    virtual void handle_recv(PlayerInfoMsg* msg);
    virtual void handle_recv(FinishGameMsg* msg);
    virtual void handle_recv(WinnerMsg* msg);

    virtual ~Handler() = default;
};

#endif  // HANDLE_H
