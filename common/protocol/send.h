#ifndef PROTOCOLOS_SEND_H
#define PROTOCOLOS_SEND_H

#include "./../messages/client_generic_msg.h"
#include "./../messages/server_generic_msg.h"

#include "protocol-socket.h"

class SendProtocol: public ProtocolSocket {
private:
    void sendHeaders(const GenericMsg& msg);

public:
    SendProtocol(Socket& socket): ProtocolSocket(socket) {}
    void send(const ExampleMsg& msg);
    void send(const LobbyListMsg& msg);
    void send(const JoinedLobbyMsg& msg);
    void send(const ServerErrorMsg& msg);
    void send(const MapInfoMsg& msg);
    void send(const PlayerInfoMsg& msg);
    void send(const FinishGameMsg& msg);
    void send(const WinnerMsg& msg);

    void send(const CustomizedPlayerInfoMsg& msg);
    void send(const ViewLobbiesMsg& msg);
    void send(const ChooseLobbyMsg& msg);
    void send(const CreateLobbyMsg& msg);
    void send(const StartGameMsg& msg);
    void send(const GoBackMsg& msg);
    void send(const PickupDropItemMsg& msg);
    void send(const StartMoveLeftMsg& msg);
    void send(const StopMoveLeftMsg& msg);
    void send(const StartMoveRightMsg& msg);
    void send(const StopMoveRightMsg& msg);
    void send(const JumpMsg& msg);
    void send(const PlayDeadMsg& msg);
    void send(const ShootMsg& msg);
};
#endif  // PROTOCOLOS_SEND_H
