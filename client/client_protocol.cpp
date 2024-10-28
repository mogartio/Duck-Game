#include "client_protocol.h"

#include <string>
#include <vector>

void ClientProtocol::sendCabecera(const GenericMsg* msg) {
    uint8_t header = msg->get_header();
    send_u_int8_t(header);
}

ClientProtocol::ClientProtocol(Socket& skt): ProtocoloCommon(skt) {}

void ClientProtocol::handle_recv(EverythingOkMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(ErrorMsg& msg) {
    std::string error_msg = recv_string();
    msg.set_error_msg(error_msg);
}

void ClientProtocol::handle_send(const ViewLobbiesMsg& msg) {
    sendCabecera(&msg);
}

void ClientProtocol::handle_send(const ChooseLobbyMsg& msg) {
    sendCabecera(&msg);
    uint8_t lobby_id = msg.get_lobby_id();
    send_u_int8_t(lobby_id);
}

void ClientProtocol::handle_send(const CreateLobbyMsg& msg) { 
    sendCabecera(&msg);
}

void ClientProtocol::handle_send(const GoBackMsg& msg) {
    sendCabecera(&msg);
}

void ClientProtocol::handle_send(const StartGameMsg& msg) { 
    sendCabecera(&msg);
}

void ClientProtocol::handle_recv(SendLobbiesListMsg& msg) {
    uint8_t lobbies_size = recv_u_int8_t();
    std::vector<std::string> lobbies;
    for (int i = 0; i < lobbies_size; i++) {
        std::string lobby_name = recv_string();
        lobbies.push_back(lobby_name);
    }
    msg.set_lobbies(lobbies);
}

void ClientProtocol::handle_send(const CustomizedPlayerInfoMsg& msg) {
    sendCabecera(&msg);
    uint8_t color = msg.get_color();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(color);
    send_string(player_name);
}

void ClientProtocol::handle_send(const PickupDropMsg& msg) {
    sendCabecera(&msg);
    uint8_t item_id = msg.get_item_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(item_id);
    send_string(player_name);
}

void ClientProtocol::handle_send(const MoveLeftMsg& msg) {
    sendCabecera(&msg);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const MoveRightMsg& msg) {
    sendCabecera(&msg);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const JumpMsg& msg) {
    sendCabecera(&msg);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const PlayDeadMsg& msg) {
    sendCabecera(&msg);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const ShootMsg& msg) {
    sendCabecera(&msg);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_recv(GameEndedMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(WinnerMsg& msg) {
    std::string winner_name = recv_string();
    msg.set_winner_name(winner_name);
}
