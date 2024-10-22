#include <vector>
#include "map/stage.h"
#include "map/csv_writer.h"
#include "player/player.h"
int main (int argc, char *argv[]) {
    CSVWriter::write_map("main_map.csv");
    Stage stage("main_map.csv");
    Coordinate coordinate_a(30, 36);
    Coordinate coordinate_b(20, 36);
    Player player_a(coordinate_a, stage, 2);
    Player player_b(coordinate_b, stage, 3);
    stage.draw_player(player_a);
    while (true){
        std::string command;
        std::cin >> command;
        stage.delete_player_from_stage(player_a); //Borro su dibujo viejo
        player_a.take_action(command);
        stage.draw_player(player_a);
        //stage.delete_player_from_stage(player_b); //Borro su dibujo viejo
        //stage.draw_player(player_b);
        stage.print();
    }
    return 0;
}
