#ifndef PROTOCOLOS_SEND_H
#define PROTOCOLOS_SEND_H

#include "./../messages/generic_msg_customizer.h"
#include "./../messages/generic_msg_game.h"
#include "./../messages/generic_msg_lobbys.h"
#include "./../messages/generic_msg_responseser.h"

#include "protocol-socket.h"

class SendProtocol: public ProtocolSocket {
protected:
    void sendHeaders(const GenericMsg& msg);

public:
    explicit SendProtocol(Socket& socket);
    // Response server
    virtual void send(const EverythingOkey& msg);
    virtual void send(const SomethingWrong& msg);

    // Lobby messages
    virtual void send(const ExampleMsg& msg);
    virtual void send(const ViewLobbiesMsg& msg);
    virtual void send(const LobbyListMsg& msg);
    virtual void send(const JoinedLobbyMsg& msg);
    virtual void send(const CreateLobbyMsg& msg);
    virtual void send(const ExitMsg& msg);
    virtual void send(const StartGameMsg& msg);

    // Customized messages
    virtual void send(const CustomizedPlayerInfoMsg& msg);
    virtual void send(const MapInfoMsg& msg);

    // Game messages
    virtual void send(const PickupDropItemMsg& msg);
    virtual void send(const StartMoveLeftMsg& msg);
    virtual void send(const StopMoveLeftMsg& msg);
    virtual void send(const StartMoveRightMsg& msg);
    virtual void send(const StopMoveRightMsg& msg);
    virtual void send(const JumpMsg& msg);
    virtual void send(const PlayDeadMsg& msg);
    virtual void send(const ShootMsg& msg);
    virtual void send(const PlayerInfoMsg& msg);
    virtual void send(const FinishGameMsg& msg);
    virtual void send(const WinnerMsg& msg);

    virtual ~SendProtocol() = default;
};
#endif  // PROTOCOLOS_SEND_H
