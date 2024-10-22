#include "player.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include "weapon.h"

Player::Player(Coordinate& initial_position, Stage& stage, int id): position(initial_position, *this, stage), id(id), is_alive(true),
stage(stage), weapon(std::move(std::make_unique<CowboyGun>(*this, stage))){}

Coordinate Player::get_position() { return position.get_position(); }

int Player::get_id() { return id; }

void Player::occupy(Coordinate& coordinate) { position.occupy(coordinate); }

std::vector<Coordinate> Player::get_occupied() { return position.get_occupied(); }

void Player::take_action(std::string& command){
    if (command.compare("x") == 0){
        shoot();
        return;
    }
    move(command);
}

void Player::move(std::string& direction){ position.move(direction); }

void Player::shoot(){ 
    weapon->shoot(position.get_facing_direction());
}

void Player::die(){ is_alive = false;}

