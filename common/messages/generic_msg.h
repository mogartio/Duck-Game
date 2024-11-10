#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

// TODO: Aca se puede directamente agregar los imports de los handlers
// TODO: No se porque se los declara tempranamente aca????
#include "descripcion-lobby.h"
#include "handler_read.h"
#include "handler_recv.h"
#include "handler_send.h"

namespace ActionsId {

enum ActionId : uint8_t {
    MOVE_LEFT = 0x01,
    MOVE_RIGHT = 0x02,
    JUMP = 0x03,
    SHOOT = 0x04,
    PLAY_DEAD = 0x05,
    AIM_UP = 0x06,
    THROW_WEAPON = 0x07,
};


}

class GenericMsg {
public:
    enum MsgTypeHeader : uint8_t {
        INFO_LOBBY_MSG = 0x00,
        CUSTOMIZED_PLAYER_INFO_MSG = 0x01,
        VIEW_LOBBIES_MSG = 0x02,
        CHOOSE_LOBBY_MSG = 0x03,
        CREATE_LOBBY_MSG = 0x04,
        GO_BACK_MSG = 0x05,
        EXIT_FROM_LOBBY_MSG = 0x06,
        START_GAME_MSG = 0x07,
        PICKUP_DROP_MSG = 0x08,
        START_ACTION_MSG = 0x09,
        STOP_ACTION_MSG = 0x0A,
        SEND_LOBBIES_LIST_MSG = 0x0B,
        EVERYTHING_OK_MSG = 0x0C,
        ERROR_MSG = 0x0D,
        SEND_MAP_MSG = 0x0E,
        GAME_ENDED_MSG = 0x0F,
        WINNER_MSG = 0x10,
        UPDATED_PLAYER_INFO_MSG = 0x11,
        PROJECTILE_INFO_MSG = 0x12,
    };

    enum Type : uint8_t {
        LOBBY_MSG = 0x01,
        GAME_MSG = 0x02,
    };


    enum FacingDirection : uint8_t {
        RIGHT = 0x01,
        LEFT = 0x02,
    };

private:
    MsgTypeHeader header;
    Type type;
    int id_client;

public:
    explicit GenericMsg(MsgTypeHeader header, Type type);

    virtual void accept_send(HandlerSender& handler) = 0;
    virtual void accept_recv(HandlerReceiver& handler) = 0;
    virtual void accept_read(HandlerReader& handler) = 0;
    uint8_t get_header() const;
    uint8_t get_type() const;
    int get_id_client() const;
    void set_id_client(int id_client);
    virtual ~GenericMsg() = default;
};

class InfoLobbyMsg: public GenericMsg {
private:
    std::list<DescipcionPlayer> players;
    uint8_t max_players;


public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    InfoLobbyMsg();

    InfoLobbyMsg(std::list<DescipcionPlayer> players, uint8_t max_players);

    void set_players(std::list<DescipcionPlayer> players);

    void set_max_players(uint8_t max_players);

    std::list<DescipcionPlayer> get_players() const;

    uint8_t get_max_players() const;
};


class CustomizedPlayerInfoMsg: public GenericMsg {
private:
    uint8_t color;
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    CustomizedPlayerInfoMsg();

    explicit CustomizedPlayerInfoMsg(uint8_t color, std::string player_name);

    uint8_t get_color() const;

    std::string get_player_name() const;

    void set_color(uint8_t color);

    void set_player_name(std::string player_name);
};

class ViewLobbiesMsg: public GenericMsg {
private:
public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    ViewLobbiesMsg();
};

class ChooseLobbyMsg: public GenericMsg {
private:
    uint8_t lobby_id;
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    ChooseLobbyMsg();

    explicit ChooseLobbyMsg(uint8_t lobby_id, std::string player_name);

    void set_lobby_id(uint8_t lobby_id);

    uint8_t get_lobby_id() const;

    std::string get_player_name() const;

    void set_player_name(std::string player_name);
};

class CreateLobbyMsg: public GenericMsg {
private:
    std::string player_name;
    std::string lobby_name;
    uint8_t max_players;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    CreateLobbyMsg();

    CreateLobbyMsg(std::string player_name, std::string lobby_name, uint8_t max_players);

    void set_player_name(std::string player_name);

    void set_lobby_name(std::string lobby_name);

    void set_max_players(uint8_t max_players);

    std::string get_player_name() const;

    std::string get_lobby_name() const;

    uint8_t get_max_players() const;
};

class GoBackMsg: public GenericMsg {
private:
public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    GoBackMsg();
};

class ExitFromLobbyMsg: public GenericMsg {
private:
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    ExitFromLobbyMsg();

    explicit ExitFromLobbyMsg(std::string player_name);

    void set_player_name(std::string player_name);

    std::string get_player_name() const;
};

class StartGameMsg: public GenericMsg {
private:
public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    StartGameMsg();
};

class PickupDropMsg: public GenericMsg {
private:
    uint8_t item_id;
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    PickupDropMsg();

    explicit PickupDropMsg(uint8_t item_id, std::string player_name);

    void set_item_id(uint8_t item_id);

    void set_player_name(std::string player_name);

    uint8_t get_item_id() const;

    std::string get_player_name() const;
};

class StartActionMsg: public GenericMsg {
private:
    uint8_t action_id;
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    StartActionMsg();

    explicit StartActionMsg(uint8_t action_id, std::string player_name);

    void set_action_id(uint8_t action_id);

    void set_player_name(std::string player_name);

    uint8_t get_action_id() const;

    std::string get_player_name() const;
};

class StopActionMsg: public GenericMsg {
private:
    uint8_t action_id;
    std::string player_name;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    StopActionMsg();

    explicit StopActionMsg(uint8_t action_id, std::string player_name);

    void set_action_id(uint8_t action_id);

    void set_player_name(std::string player_name);

    uint8_t get_action_id() const;

    std::string get_player_name() const;
};


class SendLobbiesListMsg: public GenericMsg {
private:
    std::vector<DescripcionLobby> lobbies;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    SendLobbiesListMsg();

    explicit SendLobbiesListMsg(std::vector<DescripcionLobby> lobbies);

    void set_lobbies(std::vector<DescripcionLobby> lobbies);

    std::vector<DescripcionLobby> get_lobbies() const;
};

class EverythingOkMsg: public GenericMsg {
private:
public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    EverythingOkMsg();
};

class ErrorMsg: public GenericMsg {
private:
    std::string error_msg;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    ErrorMsg();

    explicit ErrorMsg(std::string error_msg);

    void set_error_msg(std::string error_msg);

    std::string get_error_msg() const;
};

class SendMapMsg: public GenericMsg {
private:
    std::vector<uint16_t> map;  // le puse string pero no se que va
    uint16_t filas;
    uint16_t columnas;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    SendMapMsg();

    explicit SendMapMsg(std::vector<uint16_t> map, uint16_t filas, uint16_t columnas);

    void set_map(std::vector<uint16_t> map);

    std::vector<uint16_t> get_map() const;

    void set_filas(uint16_t filas);

    void set_columnas(uint16_t columnas);

    uint16_t get_filas() const;

    uint16_t get_columnas() const;
};

class GameEndedMsg: public GenericMsg {
private:
public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    GameEndedMsg();
};

class WinnerMsg: public GenericMsg {
private:
    std::string winner_name;
    // type stats (a definir)

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    WinnerMsg();

    explicit WinnerMsg(std::string winner_name);

    void set_winner_name(std::string winner_name);

    std::string get_winner_name() const;
};

class UpdatedPlayerInfoMsg: public GenericMsg {
private:
    std::string player_name;
    std::pair<uint16_t, uint16_t> position;
    uint8_t state;
    uint8_t facing_direction;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    UpdatedPlayerInfoMsg();

    explicit UpdatedPlayerInfoMsg(std::string player_name, std::pair<uint16_t, uint16_t> position,
                                  uint8_t state, uint8_t facing_direction);

    std::string get_player_name() const;

    std::pair<uint8_t, uint8_t> get_position() const;

    uint8_t get_state() const;

    uint8_t get_facing_direction() const;

    void set_player_name(std::string player_name);

    void set_position(uint8_t x, uint8_t y);

    void set_state(uint8_t state);

    void set_facing_direction(uint8_t facing_direction);
};

class ProjectileInfoMsg: public GenericMsg {
private:
    std::vector<std::pair<uint16_t, uint16_t>> projectile_trail;
    std::pair<uint16_t, uint16_t> projectile_final_position;

public:
    void accept_send(HandlerSender& handler) override;

    void accept_recv(HandlerReceiver& handler) override;

    void accept_read(HandlerReader& handler) override;

    ProjectileInfoMsg();

    explicit ProjectileInfoMsg(std::vector<std::pair<uint16_t, uint16_t>> projectile_trail,
                               std::pair<uint16_t, uint16_t> projectile_final_position);

    std::vector<std::pair<uint16_t, uint16_t>> get_projectile_trail() const;

    std::pair<uint16_t, uint16_t> get_final_position() const;

    void set_projectile_trail(std::vector<std::pair<uint16_t, uint16_t>> projectile_trail);

    void set_projectile_final_position(uint16_t x, uint16_t y);
};


#endif
