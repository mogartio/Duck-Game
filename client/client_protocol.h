#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common/protocolo-common.h"

class ClientProtocol: public ProtocoloCommon {
private:
    // ------------------- metodos -------------------
    void sendCabecera(const GenericMsg& msg);

public:
    explicit ClientProtocol(Socket& skt);

    using ProtocoloCommon::handle_recv;
    using ProtocoloCommon::handle_send;

    // RESPONSE SERVER MESSAGES
    virtual void handle_recv(EverythingOkMsg& msg) override;
    virtual void handle_recv(ErrorMsg& msg) override;

    // LOBBY MESSAGES
    virtual void handle_send(const ViewLobbiesMsg& msg) override;
    virtual void handle_send(const ChooseLobbyMsg& msg) override;
    virtual void handle_send(const CreateLobbyMsg& msg) override;
    virtual void handle_send(const GoBackMsg& msg) override;
    virtual void handle_send(const StartGameMsg& msg) override;


    virtual void handle_recv(SendLobbiesListMsg& msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg) override;

    // GAME MESSAGES
    virtual void handle_send(const PickupDropMsg& msg) override;
    virtual void handle_send(const MoveLeftMsg& msg) override;
    virtual void handle_send(const MoveRightMsg& msg) override;
    virtual void handle_send(const JumpMsg& msg) override;
    virtual void handle_send(const PlayDeadMsg& msg) override;
    virtual void handle_send(const ShootMsg& msg) override;

    virtual void handle_recv(GameEndedMsg& msg) override;
    virtual void handle_recv(WinnerMsg& msg) override;
};
#endif  // CLIENT_PROTOCOL_H
