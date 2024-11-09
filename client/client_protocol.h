#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <list>

#include "../common/protocolo-common.h"

class ClientProtocol: public ProtocoloCommon {
private:
    // ------------------- metodos -------------------

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
    virtual void handle_send(const ExitFromLobbyMsg& msg) override;
    virtual void handle_send(const StartGameMsg& msg) override;

    virtual void handle_recv(InfoLobbyMsg& msg) override;
    virtual void handle_recv(SendLobbiesListMsg& msg) override;
    virtual void handle_recv(SendMapMsg& msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg) override;

    // GAME MESSAGES
    virtual void handle_send(const PickupDropMsg& msg) override;
    virtual void handle_send(const StartActionMsg& msg) override;
    virtual void handle_send(const StopActionMsg& msg) override;

    virtual void handle_recv(GameEndedMsg& msg) override;
    virtual void handle_recv(WinnerMsg& msg) override;
    virtual void handle_recv(ProjectileInfoMsg& msg) override;
    virtual void handle_recv(UpdatedPlayerInfoMsg& msg) override;
};
#endif  // CLIENT_PROTOCOL_H
