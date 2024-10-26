#include "client_generic_msg.h"

#include "./../protocol/send.h"

CustomizedPlayerInfoMsg::CustomizedPlayerInfoMsg(): CustomizedMsg(PLAYER_INFO) {}

void CustomizedPlayerInfoMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

ViewLobbiesMsg::ViewLobbiesMsg(): LobbyMsg(VIEW_LOBBIES) {}

void ViewLobbiesMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

CreateLobbyMsg::CreateLobbyMsg(): LobbyMsg(CREATE_LOBBY) {}

void CreateLobbyMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

ChooseLobbyMsg::ChooseLobbyMsg(): LobbyMsg(CHOOSE_LOBBY) {}

void ChooseLobbyMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

StartGameMsg::StartGameMsg(): LobbyMsg(START_GAME) {}

void StartGameMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

GoBackMsg::GoBackMsg(): LobbyMsg(GO_BACK) {}

void GoBackMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

PickupDropItemMsg::PickupDropItemMsg(): GameMsg(PICKUP_DROP_ITEM) {}

void PickupDropItemMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

StartMoveLeftMsg::StartMoveLeftMsg(): GameMsg(START_MOVE_LEFT) {}

void StartMoveLeftMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

StopMoveLeftMsg::StopMoveLeftMsg(): GameMsg(STOP_MOVE_LEFT) {}

void StopMoveLeftMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

StartMoveRightMsg::StartMoveRightMsg(): GameMsg(START_MOVE_RIGHT) {}

void StartMoveRightMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

StopMoveRightMsg::StopMoveRightMsg(): GameMsg(STOP_MOVE_RIGHT) {}

void StopMoveRightMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

JumpMsg::JumpMsg(): GameMsg(JUMP) {}

void JumpMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

PlayDeadMsg::PlayDeadMsg(): GameMsg(PLAY_DEAD) {}

void PlayDeadMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }

ShootMsg::ShootMsg(): GameMsg(SHOOT) {}

void ShootMsg::accept_send(SendProtocol& protocol) { protocol.send(*this); }
