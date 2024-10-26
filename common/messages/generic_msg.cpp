#include "generic_msg.h"

GenericMsg::GenericMsg(typeMsg first_header): first_header(first_header) {}

uint8_t GenericMsg::get_first_header() const { return first_header; }

ResponseServerMsg::ResponseServerMsg(responseType second_header):
        GenericMsg(RESPONSE_SERVER), second_header(second_header) {}

uint8_t ResponseServerMsg::get_second_header() const { return second_header; }

CustomizedMsg::CustomizedMsg(customizedType second_header):
        GenericMsg(CUSTOMIZED_INFO), second_header(second_header) {}

uint8_t CustomizedMsg::get_second_header() const { return second_header; }

LobbyMsg::LobbyMsg(lobbyType second_header):
        GenericMsg(LOBBY_MESSAGE), second_header(second_header) {}

uint8_t LobbyMsg::get_second_header() const { return second_header; }

GameMsg::GameMsg(gameType second_header): GenericMsg(GAME_MESSAGE), second_header(second_header) {}

uint8_t GameMsg::get_second_header() const { return second_header; }
