#include "game_main.h"

GameMain::GameMain() {}

int GameMain::run() {
    CSVWriter::write_map("main_map.csv");
    Stage stage("main_map.csv");
    Coordinate coordinate_a(30, 36);

    Player player_a(coordinate_a, stage, 2);
    stage.draw_player(player_a);
    while (true) {
        // Aca hay que try_popear de una cola de mensajes
        // GenericMsg msg = q.pop();
        // msg.handle_read(*this);
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

void GameMain::handle_read(const PickupDropMsg& msg) {
    // No tengo idea que se hace con el pick up drop
}

void GameMain::handle_read(const StartActionMsg& msg) {
    // Primero se consigue el jugador aca
    // Despues se le agrega la accion
    // std::string player_name = msg.get_player_name();
    // player_a.add_action(msg.get_action_id());
    //  aca ya tenes toda la info del mensaje
}

void GameMain::handle_read(const StopActionMsg& msg) {
    // Primero se consigue el jugador aca
    // Despues se le agrega la accion
    // std::string player_name = msg.get_player_name();
    // player_a.add_action(msg.get_action_id());
    //  aca ya tenes toda la info del mensaje
}
