#include "server_generic_msg.h"

#include "./../protocol/send.h"

ExampleMsg::ExampleMsg(std::string& data): LobbyMsg(EXAMPLE), data(data) {}

void ExampleMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

std::string ExampleMsg::getData() const { return data; }

LobbyListMsg::LobbyListMsg(): LobbyMsg(LOBBY_LIST) {}

void LobbyListMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

JoinedLobbyMsg::JoinedLobbyMsg(): LobbyMsg(JOINED_LOBBY) {}

void JoinedLobbyMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

ServerErrorMsg::ServerErrorMsg(): ResponseServerMsg(ERROR) {}

void ServerErrorMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

MapInfoMsg::MapInfoMsg(): CustomizedMsg(MAP_INFO) {}

void MapInfoMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

PlayerInfoMsg::PlayerInfoMsg(): GameMsg(PLAYER_INFO) {}

void PlayerInfoMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

FinishGameMsg::FinishGameMsg(): GameMsg(FINISH_GAME) {}

void FinishGameMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

WinnerMsg::WinnerMsg(): GameMsg(WINNER) {}

void WinnerMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }
