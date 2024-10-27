#include "client_protocol.h"

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

void ClientProtocol::handle_recv(EverythingOkey* msg) { msg = new EverythingOkey(); }
