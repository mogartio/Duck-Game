#include "send.h"

void SendServer::sendHeaders(const GenericMsg& msg) {
    u_int8_t first_header = msg.get_first_header();
    u_int8_t second_header = msg.get_second_header();
    send_uint8_t(first_header);
    send_uint8_t(second_header);
}

void SendCient::sendHeaders(const GenericMsg& msg) {
    u_int8_t first_header = msg.get_first_header();
    u_int8_t second_header = msg.get_second_header();
    send_uint8_t(first_header);
    send_uint8_t(second_header);
}

Send::Send(Socket& socket): SendServer(socket), SendCient(socket) {}

void SendServer::sendServer(const ExampleMsg& msg) {
    sendHeaders(msg);
    std::string data = msg.getData();
    send_string(data);
}

void SendServer::sendServer(const LobbyListMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const JoinedLobbyMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const ServerErrorMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const MapInfoMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const PlayerInfoMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const FinishGameMsg& msg) { sendHeaders(msg); }

void SendServer::sendServer(const WinnerMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const CustomizedPlayerInfoMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const ViewLobbiesMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const ChooseLobbyMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const CreateLobbyMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const StartGameMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const GoBackMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const PickupDropItemMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const StartMoveLeftMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const StopMoveLeftMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const StartMoveRightMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const StopMoveRightMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const JumpMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const PlayDeadMsg& msg) { sendHeaders(msg); }

void SendCient::sendClient(const ShootMsg& msg) { sendHeaders(msg); }
