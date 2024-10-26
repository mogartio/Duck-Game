#include "server_generic_msg.h"

ExampleMsg::ExampleMsg(std::string& data): LobbyMsg(EXAMPLE), data(data) {}

std::string ExampleMsg::getData() const { return data; }

LobbyListMsg::LobbyListMsg(): LobbyMsg(LOBBY_LIST) {}

JoinedLobbyMsg::JoinedLobbyMsg(): LobbyMsg(JOINED_LOBBY) {}

ServerErrorMsg::ServerErrorMsg(): ResponseServerMsg(ERROR) {}

MapInfoMsg::MapInfoMsg(): CustomizedMsg(MAP_INFO) {}

PlayerInfoMsg::PlayerInfoMsg(): GameMsg(PLAYER_INFO) {}

FinishGameMsg::FinishGameMsg(): GameMsg(FINISH_GAME) {}

WinnerMsg::WinnerMsg(): GameMsg(WINNER) {}
