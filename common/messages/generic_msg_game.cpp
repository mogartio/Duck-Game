#include "generic_msg_game.h"

#include "handler.h"

GameMsg::GameMsg(gameType second_header): GenericMsg(GAME_MESSAGE), second_header(second_header) {}

uint8_t GameMsg::get_second_header() const { return second_header; }

PickupDropItemMsg::PickupDropItemMsg(): GameMsg(PICKUP_DROP_ITEM) {}

void PickupDropItemMsg::accept_send(Handler& protocol) { protocol.send(*this); }

StartMoveLeftMsg::StartMoveLeftMsg(): GameMsg(START_MOVE_LEFT) {}

void StartMoveLeftMsg::accept_send(Handler& protocol) { protocol.send(*this); }

StopMoveLeftMsg::StopMoveLeftMsg(): GameMsg(STOP_MOVE_LEFT) {}

void StopMoveLeftMsg::accept_send(Handler& protocol) { protocol.send(*this); }

StartMoveRightMsg::StartMoveRightMsg(): GameMsg(START_MOVE_RIGHT) {}

void StartMoveRightMsg::accept_send(Handler& protocol) { protocol.send(*this); }

StopMoveRightMsg::StopMoveRightMsg(): GameMsg(STOP_MOVE_RIGHT) {}

void StopMoveRightMsg::accept_send(Handler& protocol) { protocol.send(*this); }

JumpMsg::JumpMsg(): GameMsg(JUMP) {}

void JumpMsg::accept_send(Handler& protocol) { protocol.send(*this); }

PlayDeadMsg::PlayDeadMsg(): GameMsg(PLAY_DEAD) {}

void PlayDeadMsg::accept_send(Handler& protocol) { protocol.send(*this); }

ShootMsg::ShootMsg(): GameMsg(SHOOT) {}

void ShootMsg::accept_send(Handler& protocol) { protocol.send(*this); }

PlayerInfoMsg::PlayerInfoMsg(): GameMsg(PLAYER_INFO) {}

void PlayerInfoMsg::accept_send(Handler& protocol) { protocol.send(*this); }

FinishGameMsg::FinishGameMsg(): GameMsg(FINISH_GAME) {}

void FinishGameMsg::accept_send(Handler& protocol) { protocol.send(*this); }

WinnerMsg::WinnerMsg(): GameMsg(WINNER) {}

void WinnerMsg::accept_send(Handler& protocol) { protocol.send(*this); }
