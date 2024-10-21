#include "player.h"
#include <cstdlib>

Player::Player(Coordinate& initial_position, Stage& stage): position(initial_position, *this, stage), id(2), is_alive(true),
stage(stage){}

Coordinate Player::get_position() { return position.get_position(); }

int Player::get_id() { return id; }

void Player::occupy(Coordinate& coordinate) { position.occupy(coordinate); }

std::vector<Coordinate> Player::get_occupied() { return position.get_occupied(); }


void Player::move(std::string& direction){ position.move(direction); }

void Player::die(){ is_alive = false;}

