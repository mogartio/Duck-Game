#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <functional>
#include <map>

#include "../common/messages/handler.h"
#include "../common/protocolo-common.h"

class ServerProtocol: public ProtocoloCommon {
public:
    explicit ServerProtocol(Socket& skt);

    using Handler::handle_recv;
    using Handler::handle_send;

    virtual void handle_send(EverythingOkMsg& msg) override;
    virtual void handle_send(ErrorMsg& msg) override;

    // LOBBY MESSAGES
    virtual void handle_recv(const ViewLobbiesMsg& msg) override;
    virtual void handle_recv(const ChooseLobbyMsg& msg) override;
    virtual void handle_recv(const CreateLobbyMsg& msg) override;
    virtual void handle_recv(const GoBackMsg& msg) override;
    virtual void handle_recv(const StartGameMsg& msg) override;


    virtual void handle_send(SendLobbiesListMsg& msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_recv(const CustomizedPlayerInfoMsg& msg) override;

    // GAME MESSAGES
    virtual void handle_recv(const PickupDropMsg& msg) override;
    virtual void handle_recv(const MoveLeftMsg& msg) override;
    virtual void handle_recv(const MoveRightMsg& msg) override;
    virtual void handle_recv(const JumpMsg& msg) override;
    virtual void handle_recv(const PlayDeadMsg& msg) override;
    virtual void handle_recv(const ShootMsg& msg) override;

    virtual void handle_send(GameEndedMsg& msg) override;
    virtual void handle_send(WinnerMsg& msg) override;
};

#endif  // CLIENT_PROTOCOL_H
