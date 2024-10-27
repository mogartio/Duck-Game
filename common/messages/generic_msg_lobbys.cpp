#include "generic_msg_lobbys.h"

#include "handler.h"

LobbyMsg::LobbyMsg(lobbyType second_header):
        GenericMsg(LOBBY_MESSAGE), second_header(second_header) {}

uint8_t LobbyMsg::get_second_header() const { return second_header; }

ExampleMsg::ExampleMsg(std::string& data): LobbyMsg(EXAMPLE), data(data) {}

void ExampleMsg::accept_send(Handler& protocol) { protocol.send(*this); }

std::string ExampleMsg::getData() const { return data; }

ViewLobbiesMsg::ViewLobbiesMsg(): LobbyMsg(VIEW_LOBBIES) {}

void ViewLobbiesMsg::accept_send(Handler& protocol) { protocol.send(*this); }

LobbyListMsg::LobbyListMsg(): LobbyMsg(LOBBY_LIST) {}

void LobbyListMsg::accept_send(Handler& protocol) { protocol.send(*this); }

JoinedLobbyMsg::JoinedLobbyMsg(): LobbyMsg(JOINED_LOBBY) {}

void JoinedLobbyMsg::accept_send(Handler& protocol) { protocol.send(*this); }

CreateLobbyMsg::CreateLobbyMsg(): LobbyMsg(CREATE_LOBBY) {}

void CreateLobbyMsg::accept_send(Handler& protocol) { protocol.send(*this); }

ExitMsg::ExitMsg(): LobbyMsg(EXIT_FROM_LOBBY) {}

void ExitMsg::accept_send(Handler& protocol) { protocol.send(*this); }

StartGameMsg::StartGameMsg(): LobbyMsg(START_GAME) {}

void StartGameMsg::accept_send(Handler& protocol) { protocol.send(*this); }
