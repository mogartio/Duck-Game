#include "generic_msg.h"

GenericMsg::GenericMsg(GenericMsg::MsgTypeHeader header, Type type): header(header), type(type) {}

uint8_t GenericMsg::get_header() const { return header; }

uint8_t GenericMsg::get_type() const { return type; }

int GenericMsg::get_id_client() const { return id_client; }

void GenericMsg::set_id_client(int id_client) { this->id_client = id_client; }

InfoLobbyMsg::InfoLobbyMsg(): GenericMsg(GenericMsg::INFO_LOBBY_MSG, GenericMsg::LOBBY_MSG) {}

InfoLobbyMsg::InfoLobbyMsg(std::list<DescripcionPlayer> players, uint8_t max_players,
                           uint8_t lobby_id, uint8_t starting_game):
        GenericMsg(GenericMsg::INFO_LOBBY_MSG, GenericMsg::LOBBY_MSG),
        players(players),
        max_players(max_players),
        lobby_id(lobby_id),
        starting_game(starting_game) {}

void InfoLobbyMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void InfoLobbyMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void InfoLobbyMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void InfoLobbyMsg::set_players(std::list<DescripcionPlayer> players) { this->players = players; }

void InfoLobbyMsg::set_max_players(uint8_t max_players) { this->max_players = max_players; }

void InfoLobbyMsg::set_lobby_id(uint8_t lobby_id) { this->lobby_id = lobby_id; }

void InfoLobbyMsg::set_starting_game(uint8_t starting_game) { this->starting_game = starting_game; }

uint8_t InfoLobbyMsg::get_max_players() const { return max_players; }

uint8_t InfoLobbyMsg::get_lobby_id() const { return lobby_id; }

std::list<DescripcionPlayer> InfoLobbyMsg::get_players() const { return players; }

uint8_t InfoLobbyMsg::get_starting_game() const { return starting_game; }

CustomizedPlayerInfoMsg::CustomizedPlayerInfoMsg():
        GenericMsg(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG, GenericMsg::LOBBY_MSG),
        color(0),
        player_name("") {}
CustomizedPlayerInfoMsg::CustomizedPlayerInfoMsg(uint8_t lobby_id, uint8_t color,
                                                 std::string player_name,
                                                 std::string player_new_name, uint8_t is_ready):
        GenericMsg(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG, GenericMsg::LOBBY_MSG),
        lobby_id(lobby_id),
        color(color),
        player_name(player_name),
        player_new_name(player_new_name),
        is_ready(is_ready) {}

void CustomizedPlayerInfoMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void CustomizedPlayerInfoMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void CustomizedPlayerInfoMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void CustomizedPlayerInfoMsg::set_lobby_id(uint8_t lobby_id) { this->lobby_id = lobby_id; }

void CustomizedPlayerInfoMsg::set_color(uint8_t color) { this->color = color; }

uint8_t CustomizedPlayerInfoMsg::get_lobby_id() const { return lobby_id; }

uint8_t CustomizedPlayerInfoMsg::get_color() const { return color; }

std::string CustomizedPlayerInfoMsg::get_player_name() const { return player_name; }

void CustomizedPlayerInfoMsg::set_player_name(std::string player_name) {
    this->player_name = player_name;
}

std::string CustomizedPlayerInfoMsg::get_player_new_name() const { return player_new_name; }

void CustomizedPlayerInfoMsg::set_player_new_name(std::string player_new_name) {
    this->player_new_name = player_new_name;
}

bool CustomizedPlayerInfoMsg::get_is_ready() const { return is_ready; }

void CustomizedPlayerInfoMsg::set_is_ready(uint8_t is_ready) { this->is_ready = is_ready; }

ViewLobbiesMsg::ViewLobbiesMsg(): GenericMsg(GenericMsg::VIEW_LOBBIES_MSG, GenericMsg::LOBBY_MSG) {}

void ViewLobbiesMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ViewLobbiesMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ViewLobbiesMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }


ChooseLobbyMsg::ChooseLobbyMsg():
        GenericMsg(GenericMsg::CHOOSE_LOBBY_MSG, GenericMsg::LOBBY_MSG), lobby_id(0) {}

ChooseLobbyMsg::ChooseLobbyMsg(uint8_t lobby_id, std::string player_name):
        GenericMsg(GenericMsg::CHOOSE_LOBBY_MSG, GenericMsg::LOBBY_MSG),
        lobby_id(lobby_id),
        player_name(player_name) {}

void ChooseLobbyMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ChooseLobbyMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ChooseLobbyMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void ChooseLobbyMsg::set_lobby_id(uint8_t lobby_id) { this->lobby_id = lobby_id; }

uint8_t ChooseLobbyMsg::get_lobby_id() const { return lobby_id; }

std::string ChooseLobbyMsg::get_player_name() const { return player_name; }

void ChooseLobbyMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

CreateLobbyMsg::CreateLobbyMsg(): GenericMsg(GenericMsg::CREATE_LOBBY_MSG, GenericMsg::LOBBY_MSG) {}

CreateLobbyMsg::CreateLobbyMsg(std::string player_name, std::string lobby_name,
                               uint8_t max_players):
        GenericMsg(GenericMsg::CREATE_LOBBY_MSG, GenericMsg::LOBBY_MSG),
        player_name(player_name),
        lobby_name(lobby_name),
        max_players(max_players) {}

void CreateLobbyMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void CreateLobbyMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void CreateLobbyMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void CreateLobbyMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

void CreateLobbyMsg::set_lobby_name(std::string lobby_name) { this->lobby_name = lobby_name; }

void CreateLobbyMsg::set_max_players(uint8_t max_players) { this->max_players = max_players; }

std::string CreateLobbyMsg::get_player_name() const { return player_name; }

std::string CreateLobbyMsg::get_lobby_name() const { return lobby_name; }

uint8_t CreateLobbyMsg::get_max_players() const { return max_players; }

GoBackMsg::GoBackMsg(): GenericMsg(GenericMsg::GO_BACK_MSG, GenericMsg::LOBBY_MSG) {}

void GoBackMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void GoBackMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void GoBackMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

ExitFromLobbyMsg::ExitFromLobbyMsg():
        GenericMsg(GenericMsg::EXIT_FROM_LOBBY_MSG, GenericMsg::LOBBY_MSG), player_name("") {}

ExitFromLobbyMsg::ExitFromLobbyMsg(std::string player_name):
        GenericMsg(GenericMsg::EXIT_FROM_LOBBY_MSG, GenericMsg::LOBBY_MSG),
        player_name(player_name) {}

void ExitFromLobbyMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ExitFromLobbyMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ExitFromLobbyMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void ExitFromLobbyMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

std::string ExitFromLobbyMsg::get_player_name() const { return player_name; }

StartGameMsg::StartGameMsg(): GenericMsg(GenericMsg::START_GAME_MSG, GenericMsg::LOBBY_MSG) {}

void StartGameMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void StartGameMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void StartGameMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

PickupDropMsg::PickupDropMsg():
        GenericMsg(GenericMsg::PICKUP_DROP_MSG, GenericMsg::GAME_MSG),
        item_id(0),
        player_name("") {}

PickupDropMsg::PickupDropMsg(std::string player_name, uint8_t item_id):
        GenericMsg(GenericMsg::PICKUP_DROP_MSG, GenericMsg::GAME_MSG),
        item_id(item_id),
        player_name(player_name) {}

void PickupDropMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void PickupDropMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void PickupDropMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void PickupDropMsg::set_item_id(uint8_t item_id) { this->item_id = item_id; }

void PickupDropMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

uint8_t PickupDropMsg::get_item_id() const { return item_id; }

std::string PickupDropMsg::get_player_name() const { return player_name; }

StartActionMsg::StartActionMsg():
        GenericMsg(GenericMsg::START_ACTION_MSG, GenericMsg::GAME_MSG),
        action_id(0),
        player_name("") {}

StartActionMsg::StartActionMsg(uint8_t action_id, std::string player_name):
        GenericMsg(GenericMsg::START_ACTION_MSG, GenericMsg::GAME_MSG),
        action_id(action_id),
        player_name(player_name) {}

void StartActionMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void StartActionMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void StartActionMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void StartActionMsg::set_action_id(uint8_t action_id) { this->action_id = action_id; }

void StartActionMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

uint8_t StartActionMsg::get_action_id() const { return action_id; }

std::string StartActionMsg::get_player_name() const { return player_name; }

StopActionMsg::StopActionMsg():
        GenericMsg(GenericMsg::STOP_ACTION_MSG, GenericMsg::GAME_MSG),
        action_id(0),
        player_name("") {}

StopActionMsg::StopActionMsg(uint8_t action_id, std::string player_name):
        GenericMsg(GenericMsg::STOP_ACTION_MSG, GenericMsg::GAME_MSG),
        action_id(action_id),
        player_name(player_name) {}

void StopActionMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void StopActionMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void StopActionMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void StopActionMsg::set_action_id(uint8_t action_id) { this->action_id = action_id; }

void StopActionMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

uint8_t StopActionMsg::get_action_id() const { return action_id; }

std::string StopActionMsg::get_player_name() const { return player_name; }

SendLobbiesListMsg::SendLobbiesListMsg():
        GenericMsg(GenericMsg::SEND_LOBBIES_LIST_MSG, GenericMsg::LOBBY_MSG) {}

SendLobbiesListMsg::SendLobbiesListMsg(std::vector<DescripcionLobby> lobbies):
        GenericMsg(GenericMsg::SEND_LOBBIES_LIST_MSG, GenericMsg::LOBBY_MSG), lobbies(lobbies) {}

void SendLobbiesListMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void SendLobbiesListMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void SendLobbiesListMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void SendLobbiesListMsg::set_lobbies(std::vector<DescripcionLobby> lobbies) {
    this->lobbies = lobbies;
}

std::vector<DescripcionLobby> SendLobbiesListMsg::get_lobbies() const { return lobbies; }

EverythingOkMsg::EverythingOkMsg():
        GenericMsg(GenericMsg::EVERYTHING_OK_MSG, GenericMsg::GAME_MSG) {}

void EverythingOkMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void EverythingOkMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void EverythingOkMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

ErrorMsg::ErrorMsg(): GenericMsg(GenericMsg::ERROR_MSG, GenericMsg::GAME_MSG), error_msg("") {}

ErrorMsg::ErrorMsg(std::string error_msg):
        GenericMsg(GenericMsg::ERROR_MSG, GenericMsg::GAME_MSG), error_msg(error_msg) {}

void ErrorMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ErrorMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ErrorMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void ErrorMsg::set_error_msg(std::string error_msg) { this->error_msg = error_msg; }

std::string ErrorMsg::get_error_msg() const { return error_msg; }

SendMapMsg::SendMapMsg():
        GenericMsg(GenericMsg::SEND_MAP_MSG, GenericMsg::GAME_MSG), filas(0), columnas(0) {}

SendMapMsg::SendMapMsg(std::vector<uint16_t> map, uint16_t filas, uint16_t columnas):
        GenericMsg(GenericMsg::SEND_MAP_MSG, GenericMsg::GAME_MSG),
        map(map),
        filas(filas),
        columnas(columnas) {}

void SendMapMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void SendMapMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void SendMapMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void SendMapMsg::set_map(std::vector<uint16_t> map) { this->map = map; }

std::vector<uint16_t> SendMapMsg::get_map() const { return map; }

void SendMapMsg::set_filas(uint16_t filas) { this->filas = filas; }

void SendMapMsg::set_columnas(uint16_t columnas) { this->columnas = columnas; }

uint16_t SendMapMsg::get_filas() const { return filas; }

uint16_t SendMapMsg::get_columnas() const { return columnas; }

GameEndedMsg::GameEndedMsg(): GenericMsg(GenericMsg::GAME_ENDED_MSG, GenericMsg::GAME_MSG) {}

void GameEndedMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void GameEndedMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void GameEndedMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

WinnerMsg::WinnerMsg(): GenericMsg(GenericMsg::WINNER_MSG, GenericMsg::GAME_MSG), winner_name("") {}

WinnerMsg::WinnerMsg(std::string winner_name):
        GenericMsg(GenericMsg::WINNER_MSG, GenericMsg::GAME_MSG), winner_name(winner_name) {}

void WinnerMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void WinnerMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void WinnerMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void WinnerMsg::set_winner_name(std::string winner_name) { this->winner_name = winner_name; }

std::string WinnerMsg::get_winner_name() const { return winner_name; }

UpdatedPlayerInfoMsg::UpdatedPlayerInfoMsg():
        GenericMsg(GenericMsg::UPDATED_PLAYER_INFO_MSG, GenericMsg::GAME_MSG),
        player_name(""),
        position(),
        state(0),
        facing_direction(0) {}
UpdatedPlayerInfoMsg::UpdatedPlayerInfoMsg(std::string player_name,
                                           std::pair<uint16_t, uint16_t> position, uint8_t state,
                                           uint8_t facing_direction,
                                           uint8_t facing_direction_second):
        GenericMsg(GenericMsg::UPDATED_PLAYER_INFO_MSG, GenericMsg::GAME_MSG),
        player_name(player_name),
        position(position),
        state(state),
        facing_direction(facing_direction),
        facing_direction_second(facing_direction_second) {}

void UpdatedPlayerInfoMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void UpdatedPlayerInfoMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void UpdatedPlayerInfoMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

std::string UpdatedPlayerInfoMsg::get_player_name() const { return player_name; }

std::pair<uint8_t, uint8_t> UpdatedPlayerInfoMsg::get_position() const { return position; }

uint8_t UpdatedPlayerInfoMsg::get_state() const { return state; }

uint8_t UpdatedPlayerInfoMsg::get_facing_direction() const { return facing_direction; }

void UpdatedPlayerInfoMsg::set_player_name(std::string player_name) {
    this->player_name = player_name;
}

void UpdatedPlayerInfoMsg::set_position(uint8_t x, uint8_t y) {
    this->position = std::make_pair(x, y);
}

void UpdatedPlayerInfoMsg::set_state(uint8_t state) { this->state = state; }

void UpdatedPlayerInfoMsg::set_facing_direction(uint8_t facing_direction) {
    this->facing_direction = facing_direction;
}

uint8_t UpdatedPlayerInfoMsg::get_facing_direction_second() const {
    return facing_direction_second;
}

void UpdatedPlayerInfoMsg::set_facing_direction_second(uint8_t facing_direction_second) {
    this->facing_direction_second = facing_direction_second;
}

ProjectileInfoMsg::ProjectileInfoMsg():
        GenericMsg(GenericMsg::PROJECTILE_INFO_MSG, GenericMsg::GAME_MSG),
        pos_x(),
        pos_y(),
        item() {}

ProjectileInfoMsg::ProjectileInfoMsg(std::vector<std::pair<uint8_t, uint8_t>> trail, uint8_t pos_x,
                                     uint8_t pos_y, uint8_t item, uint8_t facing_direction_first,
                                     uint8_t facing_direction_second):
        GenericMsg(GenericMsg::PROJECTILE_INFO_MSG, GenericMsg::GAME_MSG),
        pos_x(pos_x),
        pos_y(pos_y),
        item(item),
        trail(trail),
        facing_direction_first(facing_direction_first),
        facing_direction_second(facing_direction_second) {}

void ProjectileInfoMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ProjectileInfoMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ProjectileInfoMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

uint8_t ProjectileInfoMsg::get_pos_x() const { return pos_x; }

uint8_t ProjectileInfoMsg::get_pos_y() const { return pos_y; }

uint8_t ProjectileInfoMsg::get_item() const { return item; }

std::vector<std::pair<uint8_t, uint8_t>> ProjectileInfoMsg::get_trail() const { return trail; }

void ProjectileInfoMsg::set_pos_x(uint8_t pos_x) { this->pos_x = pos_x; }

void ProjectileInfoMsg::set_pos_y(uint8_t pos_y) { this->pos_y = pos_y; }

void ProjectileInfoMsg::set_item(uint8_t item) { this->item = item; }

void ProjectileInfoMsg::set_trail(std::vector<std::pair<uint8_t, uint8_t>> trail) {
    this->trail = trail;
}

uint8_t ProjectileInfoMsg::get_facing_direction_first() const { return facing_direction_first; }

uint8_t ProjectileInfoMsg::get_facing_direction_second() const { return facing_direction_second; }

void ProjectileInfoMsg::set_facing_direction_first(uint8_t facing_direction_first) {
    this->facing_direction_first = facing_direction_first;
}

void ProjectileInfoMsg::set_facing_direction_second(uint8_t facing_direction_second) {
    this->facing_direction_second = facing_direction_second;
}

PlayerInfoMsg::PlayerInfoMsg():
        GenericMsg(GenericMsg::PLAYER_INFO_MSG, GenericMsg::LOBBY_MSG), player_name(""), color(0) {}

PlayerInfoMsg::PlayerInfoMsg(std::string player_name, uint8_t color):
        GenericMsg(GenericMsg::PLAYER_INFO_MSG, GenericMsg::LOBBY_MSG),
        player_name(player_name),
        color(color) {}

void PlayerInfoMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void PlayerInfoMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void PlayerInfoMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

std::string PlayerInfoMsg::get_player_name() const { return player_name; }

uint8_t PlayerInfoMsg::get_color() const { return color; }

void PlayerInfoMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

void PlayerInfoMsg::set_color(uint8_t color) { this->color = color; }

NotProyectileInfo::NotProyectileInfo():
        GenericMsg(GenericMsg::NOT_PROJECTILE_INFO, GenericMsg::GAME_MSG),
        item(0),
        position_x_y() {}

NotProyectileInfo::NotProyectileInfo(uint8_t item, std::pair<uint8_t, uint8_t> position_x_y):
        GenericMsg(GenericMsg::NOT_PROJECTILE_INFO, GenericMsg::GAME_MSG),
        item(item),
        position_x_y(position_x_y) {}

void NotProyectileInfo::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void NotProyectileInfo::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void NotProyectileInfo::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void NotProyectileInfo::set_item(uint8_t item) { this->item = item; }

void NotProyectileInfo::set_position_x_y(std::pair<uint8_t, uint8_t> position_x_y) {
    this->position_x_y = position_x_y;
}

uint8_t NotProyectileInfo::get_item() const { return item; }

std::pair<uint8_t, uint8_t> NotProyectileInfo::get_position_x_y() const { return position_x_y; }

ShootMsg::ShootMsg():
        GenericMsg(GenericMsg::SHOOT_MSG, GenericMsg::GAME_MSG), player_name(""), position_x_y() {}

ShootMsg::ShootMsg(std::string player_name, std::pair<uint8_t, uint8_t> position_x_y):
        GenericMsg(GenericMsg::SHOOT_MSG, GenericMsg::GAME_MSG),
        player_name(player_name),
        position_x_y(position_x_y) {}

void ShootMsg::accept_send(HandlerSender& handler) { handler.handle_send(*this); }

void ShootMsg::accept_recv(HandlerReceiver& handler) { handler.handle_recv(*this); }

void ShootMsg::accept_read(HandlerReader& handler) { handler.handle_read(*this); }

void ShootMsg::set_player_name(std::string player_name) { this->player_name = player_name; }

void ShootMsg::set_position_x_y(std::pair<uint8_t, uint8_t> position_x_y) {
    this->position_x_y = position_x_y;
}

std::string ShootMsg::get_player_name() const { return player_name; }

std::pair<uint8_t, uint8_t> ShootMsg::get_position_x_y() const { return position_x_y; }
