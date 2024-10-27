#include "send.h"

SendProtocol::SendProtocol(Socket& socket): ProtocolSocket(socket) {}

void SendProtocol::sendHeaders(const GenericMsg& msg) {
    u_int8_t first_header = msg.get_first_header();
    u_int8_t second_header = msg.get_second_header();
    send_uint8_t(first_header);
    send_uint8_t(second_header);
}

void SendProtocol::send(const EverythingOkey& msg) { (void)msg; }

void SendProtocol::send(const SomethingWrong& msg) { (void)msg; }

void SendProtocol::send(const ExampleMsg& msg) { (void)msg; }

void SendProtocol::send(const ViewLobbiesMsg& msg) { (void)msg; }

void SendProtocol::send(const LobbyListMsg& msg) { (void)msg; }

void SendProtocol::send(const JoinedLobbyMsg& msg) { (void)msg; }

void SendProtocol::send(const CreateLobbyMsg& msg) { (void)msg; }

void SendProtocol::send(const ExitMsg& msg) { (void)msg; }

void SendProtocol::send(const StartGameMsg& msg) { (void)msg; }

void SendProtocol::send(const CustomizedPlayerInfoMsg& msg) { (void)msg; }

void SendProtocol::send(const MapInfoMsg& msg) { (void)msg; }

void SendProtocol::send(const PickupDropItemMsg& msg) { (void)msg; }

void SendProtocol::send(const StartMoveLeftMsg& msg) { (void)msg; }

void SendProtocol::send(const StopMoveLeftMsg& msg) { (void)msg; }

void SendProtocol::send(const StartMoveRightMsg& msg) { (void)msg; }

void SendProtocol::send(const StopMoveRightMsg& msg) { (void)msg; }

void SendProtocol::send(const JumpMsg& msg) { (void)msg; }

void SendProtocol::send(const PlayDeadMsg& msg) { (void)msg; }

void SendProtocol::send(const ShootMsg& msg) { (void)msg; }

void SendProtocol::send(const PlayerInfoMsg& msg) { (void)msg; }

void SendProtocol::send(const FinishGameMsg& msg) { (void)msg; }

void SendProtocol::send(const WinnerMsg& msg) { (void)msg; }
