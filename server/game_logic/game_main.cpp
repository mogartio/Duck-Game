#include <vector>
#include "stage.h"
#include "csv_writer.h"
#include "player/player.h"
int main (int argc, char *argv[]) {
    CSVWriter::write_map("main_map.csv");
    Stage stage("main_map.csv");
    int x = 30;
    int y = 36;
    Coordinate coordinate(x, y);
    Player player(coordinate, stage);
    stage.draw_player(player);
    while (true){
        stage.delete_player_from_stage(player); //Borro su dibujo viejo
        std::string command;
        std::cin >> command;
        player.move(command);
        stage.draw_player(player);
        stage.print();
    }
    return 0;
}

//g++ game_main.cpp stage.cpp player.cpp -o game
