#include "client_protocol.h"

#include <string>

ClientProtocol::ClientProtocol(Socket& skt): ProtocoloCommon(skt) {
    recv_handlers[GenericMsg::typeMsg::RESPONSE_SERVER] = {
            {ResponseServerMsg::responseType::EVERYTHING_WENT_WELL,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<EverythingOkey*>(msg)); }},
            {ResponseServerMsg::responseType::SOMETHING_WAS_WRONG,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<SomethingWrong*>(msg)); }}};
    recv_handlers[GenericMsg::typeMsg::LOBBY_MESSAGE] = {
            {LobbyMsg::lobbyType::EXAMPLE,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<ExampleMsg*>(msg)); }},
            {LobbyMsg::lobbyType::LOBBY_LIST,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<LobbyListMsg*>(msg)); }},
    };
    recv_handlers[GenericMsg::typeMsg::GAME_MESSAGE] = {
            {GameMsg::gameType::PLAYER_INFO,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<PlayerInfoMsg*>(msg)); }},
            {GameMsg::gameType::FINISH_GAME,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<FinishGameMsg*>(msg)); }},
            {GameMsg::gameType::WINNER,
             [this](GenericMsg* msg) { this->handle_recv(dynamic_cast<WinnerMsg*>(msg)); }},
    };
}

void ClientProtocol::send(GenericMsg* msg) { msg->accept_send(*this); }

GenericMsg* ClientProtocol::receive() {
    uint8_t header = recv_u_int8_t();
    uint8_t second_header = recv_u_int8_t();
    GenericMsg* msg = nullptr;
    recv_handlers[static_cast<GenericMsg::typeMsg>(header)][second_header](msg);
    return msg;
}

void ClientProtocol::sendCabecera(const GenericMsg& msg) {
    uint8_t first_header = msg.get_first_header();
    uint8_t second_header = msg.get_second_header();
    send_u_int8_t(first_header);
    send_u_int8_t(second_header);
}

void ClientProtocol::handle_recv(EverythingOkey* msg) { msg = new EverythingOkey(); }

void ClientProtocol::handle_recv(SomethingWrong* msg) { msg = new SomethingWrong(); }

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

void ClientProtocol::handle_recv(ExampleMsg* msg) {
    std::string data = recv_string();
    msg = new ExampleMsg(data);
}

void ClientProtocol::handle_recv(LobbyListMsg* msg) { msg = new LobbyListMsg(); }

void ClientProtocol::handle_send(const CustomizedPlayerInfoMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const PickupDropItemMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StartMoveLeftMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StopMoveLeftMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StartMoveRightMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const StopMoveRightMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const JumpMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const PlayDeadMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_send(const ShootMsg& msg) { sendCabecera(msg); }

void ClientProtocol::handle_recv(const PlayerInfoMsg* msg) { msg = new PlayerInfoMsg(); }

void ClientProtocol::handle_recv(const FinishGameMsg* msg) { msg = new FinishGameMsg(); }

void ClientProtocol::handle_recv(const WinnerMsg* msg) { msg = new WinnerMsg(); }
