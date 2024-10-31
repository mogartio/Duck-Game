#include "client_protocol.h"

#include <string>
#include <vector>


ClientProtocol::ClientProtocol(Socket& skt): ProtocoloCommon(skt) {}

void ClientProtocol::handle_recv(EverythingOkMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(ErrorMsg& msg) {
    std::string error_msg = recv_string();
    msg.set_error_msg(error_msg);
}

void ClientProtocol::handle_send(const ViewLobbiesMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_send(const ChooseLobbyMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t lobby_id = msg.get_lobby_id();
    send_u_int8_t(lobby_id);
}

void ClientProtocol::handle_send(const CreateLobbyMsg& msg) { 
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_send(const GoBackMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_send(const StartGameMsg& msg) { 
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
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
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t color = msg.get_color();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(color);
    send_string(player_name);
}

void ClientProtocol::handle_send(const PickupDropMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t item_id = msg.get_item_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(item_id);
    send_string(player_name);
}

void ClientProtocol::handle_send(const StartActionMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t action_id = msg.get_action_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(action_id);
    send_string(player_name);
}

void ClientProtocol::handle_send(const StopActionMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t action_id = msg.get_action_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(action_id);
    send_string(player_name);
}

void ClientProtocol::handle_recv(GameEndedMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(WinnerMsg& msg) {
    std::string winner_name = recv_string();
    msg.set_winner_name(winner_name);
}

void ClientProtocol::handle_recv(SendMapMsg& msg) {
    uint16_t filas = recv_u_int8_t();
    msg.set_filas(filas);
    uint16_t columnas = recv_u_int8_t();
    msg.set_columnas(columnas);
    std::vector<uint16_t> map;
    for (int i = 0; i < filas; i++) {
        uint16_t tile = recv_u_int8_t();
        map.push_back(tile);
    }
    msg.set_map(map);
    uint16_t x1 = recv_u_int16_t();
    uint16_t y1 = recv_u_int16_t();
    msg.set_player1_spawn(x1, y1);
    uint16_t x2 = recv_u_int16_t();
    uint16_t y2 = recv_u_int16_t();
    msg.set_player2_spawn(x2, y2);
    
}

void ClientProtocol::handle_recv(ProjectileInfoMsg& msg) {
    // recibo la cantidad de posiciones que tiene el trail
    uint16_t trail_size = recv_u_int16_t();
    // recibo las posiciones del trail
    std::vector<std::pair<uint16_t, uint16_t>> trail;
    for (int i = 0; i < trail_size; i++) {
        uint16_t x = recv_u_int16_t();
        uint16_t y = recv_u_int16_t();
        trail.push_back(std::make_pair(x, y));
    }
    // recibo la posicion final
    uint16_t x = recv_u_int16_t();
    uint16_t y = recv_u_int16_t();
    // seteo los valores en el mensaje
    msg.set_projectile_trail(trail);
    msg.set_projectile_final_position(x, y);
}

void ClientProtocol::handle_recv(UpdatedPlayerInfoMsg& msg) {
    std::string player_name = recv_string();
    uint16_t x = recv_u_int16_t();
    uint16_t y = recv_u_int16_t();
    uint8_t state = recv_u_int8_t();
    uint8_t facing_direction = recv_u_int8_t();
    msg.set_player_name(player_name);
    msg.set_position(x, y);
    msg.set_state(state);
    msg.set_facing_direction(facing_direction);
}