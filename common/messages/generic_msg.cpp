#include "generic_msg.h"

#include <iomanip>
#include <utility>

#include "handler_read.h"
#include "handler_recv.h"
#include "handler_send.h"

class CustomizedPlayerInfoMsg: public GenericMsg {
private:
    uint8_t color;
    std::string player_name;
    uint8_t header;

public:
    CustomizedPlayerInfoMsg():
            color(0), player_name(""), header(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG) {}
    explicit CustomizedPlayerInfoMsg(uint8_t color, std::string player_name):
            color(color),
            player_name(player_name),
            header(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_color() const { return color; }

    std::string get_player_name() const { return player_name; }

    uint8_t get_header() const { return header; }

    void set_color(uint8_t color) { this->color = color; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }
};

class ViewLobbiesMsg: public GenericMsg {
private:
    uint8_t header;

public:
    ViewLobbiesMsg(): header(GenericMsg::VIEW_LOBBIES_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class ChooseLobbyMsg: public GenericMsg {
private:
    uint8_t lobby_id;
    uint8_t header;

public:
    ChooseLobbyMsg(): lobby_id(0), header(GenericMsg::CHOOSE_LOBBY_MSG) {}
    explicit ChooseLobbyMsg(uint8_t lobby_id):
            lobby_id(lobby_id), header(GenericMsg::CHOOSE_LOBBY_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_lobby_id(uint8_t lobby_id) { this->lobby_id = lobby_id; }

    uint8_t get_lobby_id() const { return lobby_id; }
};

class CreateLobbyMsg: public GenericMsg {
private:
    uint8_t header;

public:
    CreateLobbyMsg(): header(GenericMsg::CREATE_LOBBY_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class GoBackMsg: public GenericMsg {
private:
    uint8_t header;

public:
    GoBackMsg(): header(GenericMsg::GO_BACK_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class ExitFromLobbyMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    ExitFromLobbyMsg(): player_name(""), header(GenericMsg::EXIT_FROM_LOBBY_MSG) {}
    explicit ExitFromLobbyMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::EXIT_FROM_LOBBY_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }
};

class StartGameMsg: public GenericMsg {
private:
    uint8_t header;

public:
    StartGameMsg(): header(GenericMsg::START_GAME_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class PickupDropMsg: public GenericMsg {
private:
    uint8_t item_id;
    std::string player_name;
    uint8_t header;

public:
    PickupDropMsg(): item_id(0), player_name(""), header(GenericMsg::PICKUP_DROP_MSG) {}
    explicit PickupDropMsg(uint8_t item_id, std::string player_name):
            item_id(item_id), player_name(player_name), header(GenericMsg::PICKUP_DROP_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_item_id(uint8_t item_id) { this->item_id = item_id; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    uint8_t get_item_id() const { return item_id; }

    std::string get_player_name() const { return player_name; }
};

class StartActionMsg: public GenericMsg {
private:
    uint8_t action_id;
    std::string player_name;
    uint8_t header;

public:
    StartActionMsg(): action_id(0), player_name(""), header(GenericMsg::START_ACTION_MSG) {}
    explicit StartActionMsg(uint8_t action_id, std::string player_name):
            action_id(action_id), player_name(player_name), header(GenericMsg::START_ACTION_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_action_id(uint8_t action_id) { this->action_id = action_id; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    uint8_t get_action_id() const { return action_id; }

    std::string get_player_name() const { return player_name; }
};

class StopActionMsg: public GenericMsg {
private:
    uint8_t action_id;
    std::string player_name;
    uint8_t header;

public:
    StopActionMsg(): action_id(0), player_name(""), header(GenericMsg::STOP_ACTION_MSG) {}
    explicit StopActionMsg(uint8_t action_id, std::string player_name):
            action_id(action_id), player_name(player_name), header(GenericMsg::STOP_ACTION_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_action_id(uint8_t action_id) { this->action_id = action_id; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    uint8_t get_action_id() const { return action_id; }

    std::string get_player_name() const { return player_name; }
};


class SendLobbiesListMsg: public GenericMsg {
private:
    std::vector<std::string> lobbies;
    uint8_t header;

public:
    SendLobbiesListMsg(): header(GenericMsg::SEND_LOBBIES_LIST_MSG) {}
    explicit SendLobbiesListMsg(std::vector<std::string> lobbies):
            lobbies(lobbies), header(GenericMsg::SEND_LOBBIES_LIST_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_lobbies(std::vector<std::string> lobbies) { this->lobbies = lobbies; }

    std::vector<std::string> get_lobbies() const { return lobbies; }
};

class EverythingOkMsg: public GenericMsg {
private:
    uint8_t header;

public:
    EverythingOkMsg(): header(GenericMsg::EVERYTHING_OK_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class ErrorMsg: public GenericMsg {
private:
    std::string error_msg;
    uint8_t header;

public:
    ErrorMsg(): error_msg(""), header(GenericMsg::ERROR_MSG) {}
    explicit ErrorMsg(std::string error_msg): error_msg(error_msg), header(GenericMsg::ERROR_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_error_msg(std::string error_msg) { this->error_msg = error_msg; }

    std::string get_error_msg() const { return error_msg; }
};

class SendMapMsg: public GenericMsg {
private:
    std::vector<uint16_t> map;  // le puse string pero no se que va
    uint16_t filas;
    uint16_t columnas;
    uint8_t header;

public:
    SendMapMsg(): filas(0), columnas(0), header(GenericMsg::SEND_MAP_MSG) {}
    explicit SendMapMsg(std::vector<uint16_t> map, uint16_t filas, uint16_t columnas):
            map(map), filas(filas), columnas(columnas), header(GenericMsg::SEND_MAP_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_map(std::vector<uint16_t> map) { this->map = map; }

    std::vector<uint16_t> get_map() const { return map; }

    void set_filas(uint16_t filas) { this->filas = filas; }

    void set_columnas(uint16_t columnas) { this->columnas = columnas; }

    uint16_t get_filas() const { return filas; }

    uint16_t get_columnas() const { return columnas; }
};

class GameEndedMsg: public GenericMsg {
private:
    uint8_t header;

public:
    GameEndedMsg(): header(GenericMsg::GAME_ENDED_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }
};

class WinnerMsg: public GenericMsg {
private:
    std::string winner_name;
    // type stats (a definir)
    uint8_t header;

public:
    WinnerMsg(): winner_name(""), header(GenericMsg::WINNER_MSG) {}
    explicit WinnerMsg(std::string winner_name):
            winner_name(winner_name), header(GenericMsg::WINNER_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    uint8_t get_header() const { return header; }

    void set_winner_name(std::string winner_name) { this->winner_name = winner_name; }

    std::string get_winner_name() const { return winner_name; }
};

class UpdatedPlayerInfoMsg: public GenericMsg {
private:
    std::string player_name;
    std::pair<uint16_t, uint16_t> position;
    uint8_t state;
    uint8_t facing_direction;
    uint8_t header;

public:
    UpdatedPlayerInfoMsg():
            player_name(""),
            position(),
            state(0),
            facing_direction(0),
            header(GenericMsg::UPDATED_PLAYER_INFO_MSG) {}
    explicit UpdatedPlayerInfoMsg(std::string player_name, std::pair<uint16_t, uint16_t> position,
                                  uint8_t state, uint8_t facing_direction):
            player_name(player_name),
            position(position),
            state(state),
            facing_direction(facing_direction),
            header(GenericMsg::UPDATED_PLAYER_INFO_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    std::string get_player_name() const { return player_name; }

    std::pair<uint8_t, uint8_t> get_position() const { return position; }

    uint8_t get_header() const { return header; }

    uint8_t get_state() const { return state; }

    uint8_t get_facing_direction() const { return facing_direction; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    void set_position(uint8_t x, uint8_t y) { this->position = std::make_pair(x, y); }

    void set_state(uint8_t state) { this->state = state; }

    void set_facing_direction(uint8_t facing_direction) {
        this->facing_direction = facing_direction;
    }
};

class ProjectileInfoMsg: public GenericMsg {
private:
    std::vector<std::pair<uint16_t, uint16_t>> projectile_trail;
    std::pair<uint16_t, uint16_t> projectile_final_position;
    uint8_t header;

public:
    ProjectileInfoMsg():
            projectile_trail(),
            projectile_final_position(),
            header(GenericMsg::PROJECTILE_INFO_MSG) {}
    explicit ProjectileInfoMsg(std::vector<std::pair<uint16_t, uint16_t>> projectile_trail,
                               std::pair<uint16_t, uint16_t> projectile_final_position):
            projectile_trail(projectile_trail),
            projectile_final_position(projectile_final_position),
            header(GenericMsg::PROJECTILE_INFO_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    void accept_read(HandlerReader& handler) override { handler.handle_read(*this); }

    std::vector<std::pair<uint16_t, uint16_t>> get_projectile_trail() const {
        return projectile_trail;
    }

    std::pair<uint16_t, uint16_t> get_final_position() const { return projectile_final_position; }

    void set_projectile_trail(std::vector<std::pair<uint16_t, uint16_t>> projectile_trail) {
        this->projectile_trail = projectile_trail;
    }

    void set_projectile_final_position(uint16_t x, uint16_t y) {
        this->projectile_final_position = std::make_pair(x, y);
    }

    uint8_t get_header() const { return header; }
};
