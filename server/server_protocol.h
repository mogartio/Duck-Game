#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <functional>
#include <map>

#include "../common/messages/handler.h"
#include "../common/protocolo-common.h"

class ServerProtocol: public ProtocoloCommon, public Handler {
private:
    std::map<GenericMsg::typeMsg, std::map<uint8_t, std::function<GenericMsg*()>>> recv_handlers;

    void sendCabecera(const GenericMsg& msg);

public:
    explicit ServerProtocol(Socket& skt);

    void send(GenericMsg* msg);

    GenericMsg* receive();

    using Handler::handle_recv;
    using Handler::handle_send;

    // RESPONSE SERVER MESSAGES
    virtual void handle_send(const EverythingOkey& msg) override;
    virtual void handle_send(const SomethingWrong& msg) override;

    // LOBBY MESSAGES
    virtual void handle_recv(ExampleMsg** msg) override;
    virtual void handle_recv(ViewLobbiesMsg** msg) override;
    virtual void handle_recv(JoinedLobbyMsg** msg) override;
    virtual void handle_recv(CreateLobbyMsg** msg) override;
    virtual void handle_recv(ExitMsg** msg) override;
    virtual void handle_recv(StartGameMsg** msg) override;


    virtual void handle_send(const ExampleMsg& msg) override;
    virtual void handle_send(const LobbyListMsg& msg) override;

    // CUSTOMIZED MESSAGES
    virtual void handle_recv(CustomizedPlayerInfoMsg** msg) override;

    // GAME MESSAGES
    virtual void handle_recv(PickupDropItemMsg** msg) override;
    virtual void handle_recv(StartMoveLeftMsg** msg) override;
    virtual void handle_recv(StopMoveLeftMsg** msg) override;
    virtual void handle_recv(StartMoveRightMsg** msg) override;
    virtual void handle_recv(StopMoveRightMsg** msg) override;
    virtual void handle_recv(JumpMsg** msg) override;
    virtual void handle_recv(PlayDeadMsg** msg) override;
    virtual void handle_recv(ShootMsg** msg) override;

    virtual void handle_send(const PlayerInfoMsg& msg) override;
    virtual void handle_send(const FinishGameMsg& msg) override;
    virtual void handle_send(const WinnerMsg& msg) override;
};

#endif  // CLIENT_PROTOCOL_H
