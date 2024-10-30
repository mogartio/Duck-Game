#include "game_main.h"

GameMain::GameMain(Queue<GenericMsg*>&): q(q) {
    // se puede mejorar esto haciendo que capaz reciba antes el stage por referencia
    // o capaz en el lobby cuando se elige el mapa, ahi se defina el stage antes jeje
    CSVWriter::write_map("main_map.csv");
    stage = new Stage("main_map.csv");
}

int GameMain::run() {
    Coordinate coordinate_a(30, 36);

    Player player_a(coordinate_a, *stage, 2);
    stage->draw_player(player_a);
    while (true) {
        // Aca hay que try_popear de la cola de mensajes
        GenericMsg* msg;
        /* ESTO SE PUEDE HACER ASI
        // por cada uno de los mensajes recibidos, se hace un accept_read
        while (q.try_pop(msg)) {
            msg->accept_read(*this); // Esto hace un mappeo automatico Martin el cual
            // podes pensarlo como que accept_read ----> handle_read (del GameMain)
        }*/
        // O SE PUEDE HACER ASI
        q.try_pop(msg);  // lees es una unica iteracion un solo mensaje o nada si no tenes nada en
                         // la queue
        msg->accept_read(*this);
        std::string command;
        std::cin >> command;
        stage->delete_player_from_stage(player_a);  // Borro su dibujo viejo
        player_a.add_action(command);
        player_a.update();
        stage->draw_player(player_a);
        stage->update();
        stage->print();
    }
    return 0;
}

// El accept_read te mappea a estas funciones de aca abajo

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
