#include "generic_msg.h"

#include "handler.h"

class CustomizedPlayerInfoMsg {
private: 
    uint8_t color;
    std::string player_name;
    uint8_t header;
public:
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
};

class MoveLeftMsg {
private:
    std::string player_name;
    uint8_t header;

public:
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
};

class MoveRightMsg {
private:
    std::string player_name;
    uint8_t header;

public:
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
};

class JumpMsg {
private:
    std::string player_name;
    uint8_t header;

public:
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
};

class PlayDeadMsg {
private:
    std::string player_name;
    uint8_t header;

public:
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
};

class ShootMsg {
private:
    std::string player_name;
    uint8_t header;

public:
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
};

class SendLobbiesListMsg {
private:
    std::vector<std::string> lobbies;
    uint8_t header;

public:
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
};

class SendMapMsg {
private:
    std::vector<std::string> map; // le puse string pero no se que va
    uint8_t header;

public:
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
};

