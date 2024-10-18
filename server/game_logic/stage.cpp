#include "stage.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3 // actualmente los patos son cuadrados de 2X2
#include "player.h"

Stage::Stage(std::vector<Player>& players): matrix(), players(players){
    draw_initial_state();
}

void Stage::draw_initial_state(){
    for (int i=0; i < ROW_NUMBER; i++){
        for (int j=0; j < COLUMN_NUMBER; j++){
            if ((j == 40 || j ==  41) && i > 10 && i < 40){
                matrix[i][j] = FLOOR;
                continue;
            }
            matrix[i][j] = BACKGROUND;
        }
    }
    add_players_to_stage();
    printStage();
}

void Stage::add_players_to_stage(){
    for (auto& player : players){
        Coordinate position = player.get_position();
        int x = position.x;
        int y = position.y;
        for (int i=0; i < PLAYER_SIZE; i++){
            for (int j=0; j < PLAYER_SIZE; j++){
                matrix[x+i][y + j] = player.id;
            }
        }
    }
}

void Stage::printStage(){ // debugging
    for (int i=0; i < ROW_NUMBER; i++){
        std::stringstream stream;
        for (int j=0; j < COLUMN_NUMBER; j++){
            stream << "|" << matrix[j][i];
        }
        std::cout << stream.str() << std::endl; 
    }
}
