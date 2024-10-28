#include "client_protocol.h"

#include <string>

ClientProtocol::ClientProtocol(Socket& skt): ProtocoloCommon(skt) {}


void ClientProtocol::handle_recv(EverythingOkey** msg) { *msg = new EverythingOkey(); }

void ClientProtocol::handle_recv(SomethingWrong** msg) { *msg = new SomethingWrong(); }

void ClientProtocol::handle_send(const ExampleMsg& msg) {
    sendCabecera(msg);
    std::string data = msg.getData();
    send_string(data);
}

void ClientProtocol::handle_send(const ViewLobbiesMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const JoinedLobbyMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const CreateLobbyMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const ExitMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StartGameMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_recv(ExampleMsg** msg) {
    std::string data = recv_string();
    *msg = new ExampleMsg(data);
}

void ClientProtocol::handle_recv(LobbyListMsg** msg) { *msg = new LobbyListMsg(); }

void ClientProtocol::handle_send(const CustomizedPlayerInfoMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const PickupDropItemMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StartMoveLeftMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StopMoveLeftMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StartMoveRightMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StopMoveRightMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const JumpMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const PlayDeadMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const ShootMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_recv(PlayerInfoMsg** msg) { *msg = new PlayerInfoMsg(); }

void ClientProtocol::handle_recv(FinishGameMsg** msg) { *msg = new FinishGameMsg(); }

void ClientProtocol::handle_recv(WinnerMsg** msg) { *msg = new WinnerMsg(); }
