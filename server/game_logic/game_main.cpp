#include <vector>
#include "stage.h"
#include "csv_writer.h"
#include "player.h"
#define LEFT "l"
int main (int argc, char *argv[]) {
    std::vector<Player> players;
    int x = 30;
    int y = 36;
    Coordinate coordinate(x, y);
    Player player(coordinate);
    players.push_back(player);
    CSVWriter::write_map("main_map.csv");
    Stage stage(players,"main_map.csv");
    while (true){
        std::string command;
        std::cin >> command;
        stage.move_player(player, command);
        stage.print();
    }
    return 0;
}

//g++ game_main.cpp stage.cpp player.cpp -o game
