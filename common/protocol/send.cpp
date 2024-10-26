#include "send.h"

void SendProtocol::sendHeaders(const GenericMsg& msg) {
    u_int8_t first_header = msg.get_first_header();
    u_int8_t second_header = msg.get_second_header();
    send_uint8_t(first_header);
    send_uint8_t(second_header);
}

void SendProtocol::send(const ExampleMsg& msg) {
    sendHeaders(msg);
    std::string data = msg.getData();
    send_string(data);
}

void SendProtocol::send(const LobbyListMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const JoinedLobbyMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const ServerErrorMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const MapInfoMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const PlayerInfoMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const FinishGameMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const WinnerMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const CustomizedPlayerInfoMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const ViewLobbiesMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const ChooseLobbyMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const CreateLobbyMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const StartGameMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const GoBackMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const PickupDropItemMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const StartMoveLeftMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const StopMoveLeftMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const StartMoveRightMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const StopMoveRightMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const JumpMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const PlayDeadMsg& msg) { sendHeaders(msg); }

void SendProtocol::send(const ShootMsg& msg) { sendHeaders(msg); }
