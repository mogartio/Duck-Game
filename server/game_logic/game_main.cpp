#include "game_main.h"

GameMain::GameMain() {}

int GameMain::run() {
    CSVWriter::write_map("main_map.csv");
    Stage stage("main_map.csv");
    Coordinate coordinate_a(30, 36);

    Player player_a(coordinate_a, stage, 2);
    stage.draw_player(player_a);
    while (true) {
        std::string command;
        std::cin >> command;
        stage.delete_player_from_stage(player_a);  // Borro su dibujo viejo
        player_a.add_action(command);
        player_a.update();
        stage.draw_player(player_a);
        stage.update();
        stage.print();
    }
    return 0;
}
