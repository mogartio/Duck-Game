#include "player.h"

#include <cstdlib>
#include <memory>

#include "../../../common/messages/generic_msg.h"
#include "weapons/pistols.h"
#include "weapons/weapon.h"

using namespace ActionsId;
Player::Player(Coordinate& initial_position, int id, std::string name, PlayerObserver* obs):
        id(id),
        is_alive(true),
        name(name),
        should_notify(true),
        initial_position(initial_position) {
    attach(obs);
}

void Player::init_for_stage(Stage* stage) {
    this->stage = stage;
    this->position = std::make_unique<PlayerPosition>(initial_position, *this, *stage);
    is_alive = true;
    weapon = std::make_unique<CowboyGun>(*stage);
    weapon->set_player(this);
    notify();
}

Coordinate Player::get_position() { return position->get_position(); }

int Player::get_facing_direction() { return position->get_facing_direction(); }


int Player::get_id() { return id; }

void Player::occupy(Coordinate& coordinate) { position->occupy(coordinate); }

std::vector<Coordinate> Player::get_occupied() { return position->get_occupied(); }

void Player::add_action(int& command) { current_actions.insert(command); }

void Player::remove_action(int& command) {
    current_actions.erase(command);
    if (command == JUMP) {  // esto va a terminar siendo un diccionario de funciones probablemente
        position->released_jump();
    }
    if (command == 6) {
        position->stop_aiming_up();
    }
    if (command == SHOOT) {
        if (weapon == nullptr) {
            return;
        }
        weapon->stop_shooting();
    }
    if (command == THROW_WEAPON) {
        if (weapon != nullptr) {
            weapon->finish_throw(position->get_facing_direction(), position->is_aiming_up(),
                                 std::move(weapon));
        }
        weapon = nullptr;
    }
}

void Player::execute(int& command) {
    if (!is_alive) {
        return;
    }
    if (command == SHOOT) {
        shoot();
        return;
    }
    if (command == THROW_WEAPON) {
        if (weapon != nullptr) {
            weapon->start_throw();
        }
    }
}

void Player::update() {
    if (!is_alive) {
        return;
    }
    should_notify = false;
    std::set<int> moving_commands;  // comandos que te emocionan son...
    for (int command: current_actions) {
        execute(command);
        if (command == 6 || command == MOVE_LEFT || command == MOVE_RIGHT || command == JUMP) {
            moving_commands.insert(command);
        }
    }
    move(moving_commands);
    if (weapon != nullptr) {
        weapon->update();
    }
    if (should_notify) {
        notify();
    }
}

void Player::notify() {
    Coordinate current_position = position->get_position();
    for (PlayerObserver* obs: observers) {
        obs->update(name, current_position.x, current_position.y, position->get_state(),
                    position->get_facing_direction());
    }
}

void Player::move(std::set<int>& movements) { position->move(movements); }

void Player::shoot() {
    if (weapon == nullptr) {
        return;
    }
    weapon->shoot(position->get_facing_direction(), position->is_aiming_up());
}

void Player::die() { is_alive = false; }
