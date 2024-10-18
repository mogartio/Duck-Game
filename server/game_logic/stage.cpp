#include "stage.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3 // actualmente los patos son cuadrados de 2X2
#include "player.h"
#include "csv_reader.h"

Stage::Stage(std::vector<Player>& players, const std::string& file_name): map(0,0), players(players){
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
    add_players_to_stage();
}

void Stage::print(){
    map.print();
}

void Stage::add_players_to_stage(){
    for (auto& player : players){
        draw_player(player, player.get_position());
    }
}

void Stage::draw_player(Player& player, Coordinate init_position){
    int x = init_position.x;
    int y = init_position.y;
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate current(x+i, y+j);
            player.occupy(current);
            map.set(current, player.id);
        }
    }
}

void Stage::delete_player_from_stage(Player& player){
    std::vector<Coordinate> occupied = player.get_occupied();
    for (auto& coordinate : occupied){
        map.set(coordinate, BACKGROUND);
    }
    player.free_occupied();
}


void Stage::move_player(Player& player,const std::string& direction){
    int offset = 0; // La cantidad que se va a tener que mover
    Coordinate new_position = player.get_position();
    if (direction.compare("a") == 0){
        new_position = move_player_horizontal(player, -1);
    } else if (direction.compare("d") == 0) {
        new_position = move_player_horizontal(player, 1);
    } else if (direction.compare("w") == 0){
        return;
    }
    player.set_position(player.get_position());
    delete_player_from_stage(player);
    if (player_is_falling(player)){
        player.fall();
    }
    player.set_position(new_position);
    draw_player(player, new_position);
}

Coordinate Stage::move_player_horizontal(Player& player, int offset){
    Coordinate initial_pos = player.get_position();
    Coordinate new_position(initial_pos.x + offset, initial_pos.y);
    if (is_valid_position(player, new_position)){
        return new_position;
    }
    return initial_pos;
}
bool Stage::player_is_falling(Player& player){
    Coordinate current_position = player.get_position();
    Coordinate duck_feet(current_position.x, current_position.y + PLAYER_SIZE + 1);
    for (int i=0; i < PLAYER_SIZE; i ++){
        Coordinate aux(duck_feet.x + i, duck_feet.y);
        if (map.out_of_range(aux)){
            player.die();
            return true;
        }
        if (map.get(aux) == FLOOR){
            return false;
        }
    }
    return true;
}

bool Stage::is_valid_position(Player& player, Coordinate position){
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate aux(position.x + j, position.y + i);
            if (map.out_of_range(aux)){
                return false;
            }
            int value = map.get(aux);
            if (value != BACKGROUND && value != player.id){
                return false;
            }
        }
    }
    return true;
}
