#include "server_protocol.h"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

ServerProtocol::ServerProtocol(Socket& skt): ProtocoloCommon(skt) {}

void ServerProtocol::handle_send(const EverythingOkMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ServerProtocol::handle_send(const ErrorMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::string error_msg = msg.get_error_msg();
    send_string(error_msg);
}

void ServerProtocol::handle_recv(ViewLobbiesMsg& msg) { (void)msg; }

void ServerProtocol::handle_recv(ChooseLobbyMsg& msg) {
    uint8_t lobby_id = recv_u_int8_t();
    msg.set_lobby_id(lobby_id);
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

void ServerProtocol::handle_recv(CreateLobbyMsg& msg) {
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

void ServerProtocol::handle_recv(GoBackMsg& msg) { (void)msg; }

void ServerProtocol::handle_recv(StartGameMsg& msg) { (void)msg; }

void ServerProtocol::handle_recv(ExitFromLobbyMsg& msg) {
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

void ServerProtocol::handle_send(const InfoLobbyMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);

    std::list<DescipcionPlayer> players_from_lobby = msg.get_players();
    uint8_t players_size = players_from_lobby.size();
    send_u_int8_t(players_size);

    for (auto& player: players_from_lobby) {
        send_string(player.nombre);
        send_u_int8_t(player.color);
    }
}

void ServerProtocol::handle_send(const SendLobbiesListMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::vector<DescripcionLobby> lobbies = msg.get_lobbies();
    // mando el numero de lobbies
    uint8_t lobbies_size = lobbies.size();
    send_u_int8_t(lobbies_size);
    // mando los nombres de los lobbies
    for (auto& lobby: lobbies) {
        send_u_int8_t(lobby.idLobby);
        send_string(lobby.nombreLobby);
        send_u_int8_t(lobby.cantidadJugadores);
    }
}


void ServerProtocol::handle_send(const PickupDropMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t item_id = msg.get_item_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(item_id);
    send_string(player_name);
}

void ServerProtocol::handle_send(const SendMapMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    // mando filas y columnas
    uint16_t filas = msg.get_filas();
    send_u_int16_t(filas);
    uint16_t columnas = msg.get_columnas();
    send_u_int16_t(columnas);
    // mando el mapa
    std::vector<uint16_t> map = msg.get_map();
    for (size_t i = 0; i < map.size(); i++) {
        send_u_int16_t(map[i]);
    }
}

void ServerProtocol::handle_recv(CustomizedPlayerInfoMsg& msg) {
    uint8_t color = recv_u_int8_t();
    msg.set_color(color);
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

// void ServerProtocol::handle_recv(PickupDropMsg& msg) {
//     uint8_t item_id = recv_u_int8_t();
//     msg.set_item_id(item_id);
//     std::string player_name = recv_string();
//     msg.set_player_name(player_name);
// }

void ServerProtocol::handle_recv(StartActionMsg& msg) {
    uint8_t action_id = recv_u_int8_t();
    msg.set_action_id(action_id);
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

void ServerProtocol::handle_recv(StopActionMsg& msg) {
    uint8_t action_id = recv_u_int8_t();
    msg.set_action_id(action_id);
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
}

void ServerProtocol::handle_send(const GameEndedMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ServerProtocol::handle_send(const WinnerMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::string player_name = msg.get_winner_name();
    send_string(player_name);
}

void ServerProtocol::handle_send(const ProjectileInfoMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    // recibo posiciones x e y del proyectil
    uint8_t pos_x = msg.get_pos_x();
    send_u_int8_t(pos_x);
    uint8_t pos_y = msg.get_pos_y();
    send_u_int8_t(pos_y);
    // recibo el item del proyectil
    uint8_t item = msg.get_item();
    send_u_int8_t(item);
}

void ServerProtocol::handle_send(const UpdatedPlayerInfoMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
    std::pair<uint16_t, uint16_t> position = msg.get_position();
    send_u_int16_t(position.first);
    send_u_int16_t(position.second);
    uint8_t state = msg.get_state();
    send_u_int8_t(state);
    uint8_t facing_direction = msg.get_facing_direction();
    send_u_int8_t(facing_direction);
}
