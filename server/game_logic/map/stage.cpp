#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../player/player.h"
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3
#define LEFT "a"
#define RIGHT "d"
#define UP "w"
#include "csv_reader.h"
#include "stage.h"

Stage::Stage(const std::string& file_name): map(0,0){
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
}

void Stage::print(){
    map.print();
}

void Stage::draw_player(Player& player){
    Coordinate init_position = player.get_position();
    int x = init_position.x;
    int y = init_position.y;
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate current(x+i, y+j);
            player.occupy(current);
            map.set(current, player.get_id());
        }
    }
}

void Stage::delete_player_from_stage(Player& player){
    std::vector<Coordinate> occupied = player.get_occupied();
    for (auto& coordinate : occupied){
        map.set(coordinate, BACKGROUND);
    }
}

bool Stage::should_fall(PlayerPosition& player_position){
    Coordinate current_position = player_position.get_position();
    Coordinate duck_feet(current_position.x, current_position.y + PLAYER_SIZE);
    for (int i=0; i < PLAYER_SIZE; i ++){
        Coordinate aux(duck_feet.x + i, duck_feet.y);
        if (map.get(aux) == FLOOR){
            return false;
        }
    }
    return true;
}

bool Stage::is_valid_position(Coordinate position, int color){
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate aux(position.x + j, position.y + i);
            if (map.out_of_range(aux)){
                return false;
            }
            int value = map.get(aux);
            if (value != BACKGROUND && value != color){
                return false;
            }
        }
    }
    return true;
}

// direction es un versor del eje x. es decir es 1 o -1
void Stage::ray_trace(int& direction, int reach, Coordinate& gun_position){
    int direction_handler = direction; // para usar el mismo loop sea la direccion 1 o -1
    for (int i=0; i < reach; i ++){
        Coordinate bullet_position(gun_position.x + direction + i * direction_handler, gun_position.y);
        int next_tile = map.get(bullet_position);
        if (next_tile == -1){
            return;
        }
        if (next_tile == BACKGROUND) {
            map.set(bullet_position, 3);
        /*} else if(next_tile == PLAYER){
            kill(player); */
        } else if (next_tile == FLOOR) {
            return;
        }
    }
}
