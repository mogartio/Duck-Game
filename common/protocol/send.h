#ifndef PROTOCOLOS_SEND_H
#define PROTOCOLOS_SEND_H

#include "./../messages/client_generic_msg.h"
#include "./../messages/server_generic_msg.h"

#include "protocol-socket.h"

class SendServer: public ProtocolSocket {
private:
    void sendHeaders(const GenericMsg& msg);

public:
    SendServer(Socket& socket): ProtocolSocket(socket) {}
    void sendServer(const ExampleMsg& msg);
    void sendServer(const LobbyListMsg& msg);
    void sendServer(const JoinedLobbyMsg& msg);
    void sendServer(const ServerErrorMsg& msg);
    void sendServer(const MapInfoMsg& msg);
    void sendServer(const PlayerInfoMsg& msg);
    void sendServer(const FinishGameMsg& msg);
    void sendServer(const WinnerMsg& msg);
};

class SendCient: public ProtocolSocket {
private:
    void sendHeaders(const GenericMsg& msg);

public:
    SendCient(Socket& socket): ProtocolSocket(socket) {}
    void sendClient(const CustomizedPlayerInfoMsg& msg);
    void sendClient(const ViewLobbiesMsg& msg);
    void sendClient(const ChooseLobbyMsg& msg);
    void sendClient(const CreateLobbyMsg& msg);
    void sendClient(const StartGameMsg& msg);
    void sendClient(const GoBackMsg& msg);
    void sendClient(const PickupDropItemMsg& msg);
    void sendClient(const StartMoveLeftMsg& msg);
    void sendClient(const StopMoveLeftMsg& msg);
    void sendClient(const StartMoveRightMsg& msg);
    void sendClient(const StopMoveRightMsg& msg);
    void sendClient(const JumpMsg& msg);
    void sendClient(const PlayDeadMsg& msg);
    void sendClient(const ShootMsg& msg);
};

class Send: public SendServer, public SendCient {
public:
    Send(Socket& socket);
    ~Send() = default;
};
#endif  // PROTOCOLOS_SEND_H
