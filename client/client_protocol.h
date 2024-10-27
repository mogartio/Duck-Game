#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <functional>
#include <map>

#include "../common/messages/handler.h"
#include "../common/protocolo-common.h"

class ClientProtocol: public ProtocoloCommon, public Handler {
private:
    std::map<GenericMsg::typeMsg, std::map<uint8_t, std::function<GenericMsg*()>>> recv_handlers;

    void sendCabecera(const GenericMsg& msg);

public:
    explicit ClientProtocol(Socket& skt);

    void send(GenericMsg* msg);

    GenericMsg* receive();

    using Handler::handle_recv;
    using Handler::handle_send;

    // RESPONSE SERVER MESSAGES
    virtual void handle_recv(EverythingOkey** msg) override;
    virtual void handle_recv(SomethingWrong** msg) override;

    // LOBBY MESSAGES
    virtual void handle_send(const ExampleMsg& msg) override;
    virtual void handle_send(const ViewLobbiesMsg& msg) override;
    virtual void handle_send(const JoinedLobbyMsg& msg) override;
    virtual void handle_send(const CreateLobbyMsg& msg) override;
    virtual void handle_send(const ExitMsg& msg) override;
    virtual void handle_send(const StartGameMsg& msg) override;


    virtual void handle_recv(ExampleMsg** msg) override;
    virtual void handle_recv(LobbyListMsg** msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_send(const CustomizedPlayerInfoMsg& msg) override;

    // GAME MESSAGES
    virtual void handle_send(const PickupDropItemMsg& msg) override;
    virtual void handle_send(const StartMoveLeftMsg& msg) override;
    virtual void handle_send(const StopMoveLeftMsg& msg) override;
    virtual void handle_send(const StartMoveRightMsg& msg) override;
    virtual void handle_send(const StopMoveRightMsg& msg) override;
    virtual void handle_send(const JumpMsg& msg) override;
    virtual void handle_send(const PlayDeadMsg& msg) override;
    virtual void handle_send(const ShootMsg& msg) override;

    virtual void handle_recv(PlayerInfoMsg** msg) override;
    virtual void handle_recv(FinishGameMsg** msg) override;
    virtual void handle_recv(WinnerMsg** msg) override;
};

#endif  // CLIENT_PROTOCOL_H
