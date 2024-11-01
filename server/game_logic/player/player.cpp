#include "player.h"

#include <cstdlib>
#include <memory>

#include "../../../common/messages/generic_msg.h"

#include "weapon.h"

using namespace ActionsId;

Player::Player(Coordinate& initial_position, Stage& stage, int id):
        id(id),
        position(initial_position, *this, stage),
        is_alive(true),
        stage(stage),
        weapon(std::move(std::make_unique<Magnum>(*this, stage))) {}

Coordinate Player::get_position() { return position.get_position(); }

int Player::get_id() { return id; }

void Player::occupy(Coordinate& coordinate) { position.occupy(coordinate); }

std::vector<Coordinate> Player::get_occupied() { return position.get_occupied(); }

void Player::add_action(int& command) { current_actions.insert(command); }

void Player::remove_action(int& command) {
    current_actions.erase(command);
    if (command == JUMP) {  // esto va a terminar siendo un diccionario de funciones probablemente
        position.released_jump();
    }
    if (command == AIM_UP) {
        position.stop_aiming_up();
    }
    if (command == SHOOT) {
        weapon->stop_shooting();
    }
    if (command == THROW_WEAPON) {
        weapon->finish_throw();
    }
}

void Player::execute(int& command) {
    if (command == SHOOT) {
        shoot();
        return;
    }
    if (command == THROW_WEAPON) {
        weapon->start_throw();
    }
}

void Player::update() {
    std::set<int> moving_commands;  // comandos que te emocionan son...
    for (int command: current_actions) {
        execute(command);
        if (command == AIM_UP || command == MOVE_LEFT || command == MOVE_RIGHT || command == JUMP) {
            moving_commands.insert(command);
        }
    }
    move(moving_commands);
}

void Player::move(std::set<int>& movements) { position.move(movements); }

void Player::shoot() { weapon->shoot(position.get_facing_direction(), position.is_aiming_up()); }

void Player::die() { is_alive = false; }
