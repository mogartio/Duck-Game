#include "generic_msg.h"

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

    uint8_t get_color() const { return color; }

    std::string get_player_name() const { return player_name; }

    uint8_t get_header() const { return header; }

    void set_color(uint8_t color) { this->color = color; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    void print_info() const override {
        std::cout << "      Color: " << (int)color << std::endl;
        std::cout << "      Player name: " << player_name << std::endl;
    }
};

class ViewLobbiesMsg: public GenericMsg {
private:
    uint8_t header;

public:
    ViewLobbiesMsg(): header(GenericMsg::VIEW_LOBBIES_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      View lobbies message" << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_lobby_id(uint8_t lobby_id) { this->lobby_id = lobby_id; }

    uint8_t get_lobby_id() const { return lobby_id; }

    void print_info() const override {
        std::cout << "      Lobby id: " << (int)lobby_id << std::endl;
    }
};

class CreateLobbyMsg: public GenericMsg {
private:
    uint8_t header;

public:
    CreateLobbyMsg(): header(GenericMsg::CREATE_LOBBY_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      Create lobby message" << std::endl; }
};

class GoBackMsg: public GenericMsg {
private:
    uint8_t header;

public:
    GoBackMsg(): header(GenericMsg::GO_BACK_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      Go back message" << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
};

class StartGameMsg: public GenericMsg {
private:
    uint8_t header;

public:
    StartGameMsg(): header(GenericMsg::START_GAME_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      Start game message" << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_item_id(uint8_t item_id) { this->item_id = item_id; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    uint8_t get_item_id() const { return item_id; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override {
        std::cout << "      Item id: " << (int)item_id << std::endl;
        std::cout << "      Player name: " << player_name << std::endl;
    }
};

class MoveLeftMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    MoveLeftMsg(): player_name(""), header(GenericMsg::MOVE_LEFT_MSG) {}
    explicit MoveLeftMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::MOVE_LEFT_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
};

class MoveRightMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    MoveRightMsg(): player_name(""), header(GenericMsg::MOVE_RIGHT_MSG) {}
    explicit MoveRightMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::MOVE_RIGHT_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
};

class JumpMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    JumpMsg(): player_name(""), header(GenericMsg::JUMP_MSG) {}
    explicit JumpMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::JUMP_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
};

class PlayDeadMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    PlayDeadMsg(): player_name(""), header(GenericMsg::PLAY_DEAD_MSG) {}
    explicit PlayDeadMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::PLAY_DEAD_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
};

class ShootMsg: public GenericMsg {
private:
    std::string player_name;
    uint8_t header;

public:
    ShootMsg(): player_name(""), header(GenericMsg::SHOOT_MSG) {}
    explicit ShootMsg(std::string player_name):
            player_name(player_name), header(GenericMsg::SHOOT_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_player_name(std::string player_name) { this->player_name = player_name; }

    std::string get_player_name() const { return player_name; }

    void print_info() const override { std::cout << "      Player name: " << player_name << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_lobbies(std::vector<std::string> lobbies) { this->lobbies = lobbies; }

    std::vector<std::string> get_lobbies() const { return lobbies; }

    void print_info() const override {
        std::cout << "      Lobbies list:" << std::endl;
        for (const std::string& lobby : lobbies) {
            std::cout << "        " << lobby << std::endl;
        }
    }
};

class EverythingOkMsg: public GenericMsg {
private:
    uint8_t header;

public:
    EverythingOkMsg(): header(GenericMsg::EVERYTHING_OK_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      Everything ok message" << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_error_msg(std::string error_msg) { this->error_msg = error_msg; }

    std::string get_error_msg() const { return error_msg; }

    void print_info() const override { std::cout << "      Error message: " << error_msg << std::endl; }
};

class SendMapMsg: public GenericMsg {
private:
    std::vector<std::string> map;  // le puse string pero no se que va
    uint8_t header;

public:
    SendMapMsg(): header(GenericMsg::SEND_MAP_MSG) {}
    explicit SendMapMsg(std::vector<std::string> map): map(map), header(GenericMsg::SEND_MAP_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void set_map(std::vector<std::string> map) { this->map = map; }

    std::vector<std::string> get_map() const { return map; }

    void print_info() const override {
        std::cout << "      Map:" << std::endl;
        for (const std::string& row : map) {
            std::cout << "        " << row << std::endl;
        }
    }
};

class GameEndedMsg: public GenericMsg {
private:
    uint8_t header;

public:
    GameEndedMsg(): header(GenericMsg::GAME_ENDED_MSG) {}

    void accept_send(HandlerSender& handler) override { handler.handle_send(*this); }

    void accept_recv(HandlerReceiver& handler) override { handler.handle_recv(*this); }

    uint8_t get_header() const { return header; }

    void print_info() const override { std::cout << "      Game ended message" << std::endl; }
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

    uint8_t get_header() const { return header; }

    void set_winner_name(std::string winner_name) { this->winner_name = winner_name; }

    std::string get_winner_name() const { return winner_name; }

    void print_info() const override { std::cout << "      Winner name: " << winner_name << std::endl; }
};
