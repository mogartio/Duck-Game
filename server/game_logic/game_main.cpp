#include "game_main.h"

GameMain::GameMain(Queue<GenericMsg*>& q, std::string player_name1, std::string player_name2):
        stage("main_map.csv"), q(q), config("./server/game_logic/config.yaml") {
    CSVWriter::write_map("main_map.csv");
    Coordinate coordinate_a(30, 36);  // posicion por ahora de prueba

    players[player_name1] = new Player(coordinate_a, stage, 2);
    stage.draw_player(*players[player_name1]);
    (void)player_name2;  // para que no tire error de compilacion de q no se usa esa variable
}

int GameMain::run() {
    while (true) {
        // Aca hay que try_popear de la cola de mensajes
        GenericMsg* msg;
        bool have_command = q.try_pop(msg);
        if (have_command) {
            msg->accept_read(*this);  // esto equivale a una llamada al handle_read
        }
        for (auto& [name, player]: players) {
            stage.delete_player_from_stage(*player);  // Borro su dibujo viejo
            stage.draw_player(*player);
        }
        stage.update();
        stage.print();
        sleep(1);
    }
    return 0;
}


void GameMain::handle_read(const PickupDropMsg&) {}

void GameMain::handle_read(const StartActionMsg& msg) {
    int action = msg.get_action_id();
    players[msg.get_player_name()]->add_action(action);
}

void GameMain::handle_read(const StopActionMsg& msg) {
    int action = msg.get_action_id();
    players[msg.get_player_name()]->remove_action(action);
}
