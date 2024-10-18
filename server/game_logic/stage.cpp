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
        Coordinate position = player.get_position();
        int x = position.x;
        int y = position.y;
        for (int i=0; i < PLAYER_SIZE; i++){
            for (int j=0; j < PLAYER_SIZE; j++){
                Coordinate current(x+i, y+j);
                map.set(current, player.id);
            }
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
    std::cout << std::endl;
    map.print();
}
