#include "client_generic_msg.h"

CustomizedPlayerInfoMsg::CustomizedPlayerInfoMsg(): CustomizedMsg(PLAYER_INFO) {}

ViewLobbiesMsg::ViewLobbiesMsg(): LobbyMsg(VIEW_LOBBIES) {}

CreateLobbyMsg::CreateLobbyMsg(): LobbyMsg(CREATE_LOBBY) {}

ChooseLobbyMsg::ChooseLobbyMsg(): LobbyMsg(CHOOSE_LOBBY) {}

StartGameMsg::StartGameMsg(): LobbyMsg(START_GAME) {}

GoBackMsg::GoBackMsg(): LobbyMsg(GO_BACK) {}

PickupDropItemMsg::PickupDropItemMsg(): GameMsg(PICKUP_DROP_ITEM) {}

StartMoveLeftMsg::StartMoveLeftMsg(): GameMsg(START_MOVE_LEFT) {}

StopMoveLeftMsg::StopMoveLeftMsg(): GameMsg(STOP_MOVE_LEFT) {}

StartMoveRightMsg::StartMoveRightMsg(): GameMsg(START_MOVE_RIGHT) {}

StopMoveRightMsg::StopMoveRightMsg(): GameMsg(STOP_MOVE_RIGHT) {}

JumpMsg::JumpMsg(): GameMsg(JUMP) {}

PlayDeadMsg::PlayDeadMsg(): GameMsg(PLAY_DEAD) {}

ShootMsg::ShootMsg(): GameMsg(SHOOT) {}
