#include <vector>
#include "stage.h"
#include "player.h"

int main (int argc, char *argv[]) {
    std::vector<Player> players;
    int x = 30;
    int y = 37;
    Coordinate coordinate(x, y);
    Player player(coordinate);
    players.push_back(player);
    Stage stage(players); 
    return 0;
}

//g++ game_main.cpp stage.cpp player.cpp -o game
