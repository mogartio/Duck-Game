#include "generic_msg.h"

#include "handler.h"

class CustomizedPlayerInfoMsg {
private: 
    uint8_t color;
    std::string player_name;
    uint8_t header;
public:
    CustomizedPlayerInfoMsg() : color(0), player_name(""), header(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG) {}
    CustomizedPlayerInfoMsg(uint8_t color, std::string player_name) : color(color), player_name(player_name), header(GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_color(uint8_t color) {
        this->color = color;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

};

class ViewLobbiesMsg {
private:
    uint8_t header;

public:
    ViewLobbiesMsg() : header(GenericMsg::VIEW_LOBBIES_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class ChooseLobbyMsg {
private:
    uint8_t lobby_id;
    uint8_t header;

public:
    ChooseLobbyMsg() : lobby_id(0), header(GenericMsg::CHOOSE_LOBBY_MSG) {}
    ChooseLobbyMsg(uint8_t lobby_id) : lobby_id(lobby_id), header(GenericMsg::CHOOSE_LOBBY_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_lobby_id(uint8_t lobby_id) {
        this->lobby_id = lobby_id;
    }

    uint8_t get_lobby_id() const {
        return lobby_id;
    }
};

class CreateLobbyMsg {
private:
    uint8_t header;

public:
    CreateLobbyMsg() : header(GenericMsg::CREATE_LOBBY_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class GoBackMsg {
private:
    uint8_t header;

public:
    GoBackMsg() : header(GenericMsg::GO_BACK_MSG) {}
    GoBackMsg() : header(GenericMsg::GO_BACK_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class ExitFromLobbyMsg {
private:
    std::string player_name; 
    uint8_t header;

public: 
    ExitFromLobbyMsg() : player_name(""), header(GenericMsg::EXIT_FROM_LOBBY_MSG) {}
    ExitFromLobbyMsg(std::string player_name) : player_name(player_name), header(GenericMsg::EXIT_FROM_LOBBY_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class StartGameMsg {
private:
    uint8_t header;

public:
    StartGameMsg() : header(GenericMsg::START_GAME_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class PickupDropMsg {
private:
    uint8_t item_id;
    std::string player_name;
    uint8_t header;

public: 
    PickupDropMsg() : item_id(0), player_name(""), header(GenericMsg::PICKUP_DROP_MSG) {}
    PickupDropMsg(uint8_t item_id, std::string player_name) : item_id(item_id), player_name(player_name), header(GenericMsg::PICKUP_DROP_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_item_id(uint8_t item_id) {
        this->item_id = item_id;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    uint8_t get_item_id() const {
        return item_id;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class MoveLeftMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    MoveLeftMsg() : player_name(""), header(GenericMsg::MOVE_LEFT_MSG) {}
    MoveLeftMsg(std::string player_name) : player_name(player_name), header(GenericMsg::MOVE_LEFT_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class MoveRightMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    MoveRightMsg() : player_name(""), header(GenericMsg::MOVE_RIGHT_MSG) {}
    MoveRightMsg(std::string player_name) : player_name(player_name), header(GenericMsg::MOVE_RIGHT_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class JumpMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    JumpMsg() : player_name(""), header(GenericMsg::JUMP_MSG) {}
    JumpMsg(std::string player_name) : player_name(player_name), header(GenericMsg::JUMP_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class PlayDeadMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    PlayDeadMsg() : player_name(""), header(GenericMsg::PLAY_DEAD_MSG) {}
    PlayDeadMsg(std::string player_name) : player_name(player_name), header(GenericMsg::PLAY_DEAD_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class ShootMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    ShootMsg() : player_name(""), header(GenericMsg::SHOOT_MSG) {}
    ShootMsg(std::string player_name) : player_name(player_name), header(GenericMsg::SHOOT_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_player_name(std::string player_name) {
        this->player_name = player_name;
    }

    std::string get_player_name() const {
        return player_name;
    }
};

class SendLobbiesListMsg {
private:
    std::vector<std::string> lobbies;
    uint8_t header;

public:
    SendLobbiesListMsg() : header(GenericMsg::SEND_LOBBIES_LIST_MSG) {}
    SendLobbiesListMsg(std::vector<std::string> lobbies) : lobbies(lobbies), header(GenericMsg::SEND_LOBBIES_LIST_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_lobbies(std::vector<std::string> lobbies) {
        this->lobbies = lobbies;
    }

    std::vector<std::string> get_lobbies() const {
        return lobbies;
    }
};

class EverythingOkMsg {
private:
    uint8_t header;

public:
    EverythingOkMsg() : header(GenericMsg::EVERYTHING_OK_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class ErrorMsg {
private:
    std::string error_msg;
    uint8_t header;

public:
    ErrorMsg() : error_msg(""), header(GenericMsg::ERROR_MSG) {}
    ErrorMsg(std::string error_msg) : error_msg(error_msg), header(GenericMsg::ERROR_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_error_msg(std::string msg) {
        this->error_msg = error_msg;
    }

    std::string get_error_msg() const {
        return error_msg;
    }
};

class SendMapMsg {
private:
    std::vector<std::string> map; // le puse string pero no se que va
    uint8_t header;

public:
    SendMapMsg() : header(GenericMsg::SEND_MAP_MSG) {}
    SendMapMsg(std::vector<std::string> map) : map(map), header(GenericMsg::SEND_MAP_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_map(std::vector<std::string> map) {
        this->map = map;
    }

    std::vector<std::string> get_map() const {
        return map;
    }
};

class GameEndedMsg {
private:
    uint8_t header;

public:
    GameEndedMsg() : header(GenericMsg::GAME_ENDED_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }
};

class WinnerMsg {
private:
    std::string winner_name;
    // type stats (a definir)
    uint8_t header;

public:
    WinnerMsg() : winner_name(""), header(GenericMsg::WINNER_MSG) {}
    WinnerMsg(std::string winner_name) : winner_name(winner_name), header(GenericMsg::WINNER_MSG) {}

    void accept_send(Handler& handler) {
        handler.handle_send(*this);
    }

    void accept_recv(Handler& handler) {
        handler.handle_recv(*this);
    }

    uint8_t get_header() const {
        return header;
    }

    void set_winner_name(std::string winner_name) {
        this->winner_name = winner_name;
    }

    std::string get_winner_name() const {
        return winner_name;
    }
};

