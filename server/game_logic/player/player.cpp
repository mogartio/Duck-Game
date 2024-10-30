#include "player.h"

#include <cstdlib>
#include <memory>

#include "weapon.h"

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

void Player::add_action(std::string& command) {
    if (current_actions.count(command) == 1) {
        remove_action(command);
        return;
    }
    current_actions.insert(command);
}

void Player::remove_action(std::string& command) {
    current_actions.erase(command);
    if (command.compare("j") == 0) {  // TODO: fix
        position.released_w();
    }
    if (command.compare("w") == 0) {
        position.released_w();
    }
}

void Player::execute(std::string& command) {
    if (command.compare("x") == 0) {
        shoot();
        // TODO: ver si mantuvo apretado el boton
        return;
    }
}

void Player::update() {
    std::set<std::string> moving_commands;  // comandos que te emocionan son...
    for (std::string command: current_actions) {
        execute(command);
        if (command.compare("w") == 0 || command.compare("a") == 0 || command.compare("d") == 0 ||
            command.compare("j") == 0) {
            moving_commands.insert(command);  // TODO: emprolijar
        }
    }
    move(moving_commands);
}

void Player::move(std::set<std::string>& movements) { position.move(movements); }

void Player::shoot() { weapon->shoot(position.get_facing_direction()); }

void Player::die() { is_alive = false; }
