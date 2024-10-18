#include "stage.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3 // actualmente los patos son cuadrados de 2X2
#include "player.h"
#include "csv_reader.h"

Stage::Stage(std::vector<Player>& players, const std::string& file_name): map(0,0), players(players){
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
    add_players_to_stage();
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
            map.set(current, player.id);
        }
    }
}

void Stage::delete_player_from_stage(Player& player){
    Coordinate p_position = player.get_position();
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate aux(p_position.x + j, p_position.y + i);
            map.set(aux, BACKGROUND);
        }
    }
}


void Stage::move_player(Player& player,const std::string& direction){
    int offset = 0; // La cantidad que se va a tener que mover
    if (direction.compare("a") == 0){
        offset = -1;
    } else if (direction.compare("d") == 0) {
        offset = 1;
    } else{
        return;
    }
    Coordinate initial_pos = player.get_position();
    Coordinate new_position(initial_pos.x + offset, initial_pos.y);
    if (is_valid_position(player, new_position)){
        delete_player_from_stage(player);
        draw_player(player, new_position);
        player.set_position(new_position);
        std::cout << std::endl;
        map.print();
    }
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
