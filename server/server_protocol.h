#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <functional>
#include <map>

#include "../common/protocolo-common.h"

class ServerProtocol: public ProtocoloCommon {
private:
    // ------------------- Métodos privados -------------------
    void sendCabecera(const GenericMsg* msg);

public:
    explicit ServerProtocol(Socket& skt);

    using ProtocoloCommon::handle_recv;
    using ProtocoloCommon::handle_send;

    virtual void handle_send(const EverythingOkMsg& msg) override;
    virtual void handle_send(const ErrorMsg& msg) override;

    // LOBBY MESSAGES
    virtual void handle_recv(ViewLobbiesMsg& msg) override;
    virtual void handle_recv(ChooseLobbyMsg& msg) override;
    virtual void handle_recv(CreateLobbyMsg& msg) override;
    virtual void handle_recv(GoBackMsg& msg) override;
    virtual void handle_recv(StartGameMsg& msg) override;
    virtual void handle_recv(ExitFromLobbyMsg& msg) override;

    virtual void handle_send(const SendLobbiesListMsg& msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_recv(CustomizedPlayerInfoMsg& msg) override;

    // GAME MESSAGES
    virtual void handle_recv(PickupDropMsg& msg) override;
    virtual void handle_recv(MoveLeftMsg& msg) override;
    virtual void handle_recv(MoveRightMsg& msg) override;
    virtual void handle_recv(JumpMsg& msg) override;
    virtual void handle_recv(PlayDeadMsg& msg) override;
    virtual void handle_recv(ShootMsg& msg) override;

    virtual void handle_send(const GameEndedMsg& msg) override;
    virtual void handle_send(const WinnerMsg& msg) override;
};

#endif  // CLIENT_PROTOCOL_H
