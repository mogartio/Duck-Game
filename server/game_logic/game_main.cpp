#include "game_main.h"

#include "map/spawn_point.h"

#include "config.h"

GameMain::GameMain(Queue<GenericMsg*>& q, std::string player_name1, std::string player_name2,
                   bool is_testing):
        stage("main_map.csv"),
        q(q),
        is_testing(is_testing),
        player_name1(player_name1),
        player_name2(player_name2) {
    CSVWriter::write_map("main_map.csv");

    std::vector<std::tuple<int, int>> player_spawn_sites =
            Config::get_instance()->player_spawn_sites;
    Coordinate coordinate_a(std::get<0>(player_spawn_sites[0]), std::get<1>(player_spawn_sites[0]));
    Coordinate coordinate_b(std::get<0>(player_spawn_sites[1]), std::get<1>(player_spawn_sites[1]));

    std::vector<std::tuple<int, int>> weapon_spawn_sites =
            Config::get_instance()->weapon_spawn_sites;
    Coordinate weapon_spawn(std::get<0>(weapon_spawn_sites[0]), std::get<1>(weapon_spawn_sites[0]));
    WeaponSpawnPoint spawn(weapon_spawn, stage);

    // players[player_name1] = new Player(coordinate_a, stage, 2);
    // stage.draw_player(*players[player_name1]);
    players[player_name2] = new Player(coordinate_b, stage, 4);
    stage.draw_player(*players[player_name2]);
    // spawn.spawn_weapon();
}

void GameMain::run() {
    while (true) {
        // Aca hay que try_popear de la cola de mensajes
        if (is_testing) {
            std::string command;
            std::getline(std::cin, command);
            GenericMsg* new_msg = create_msg(command);
            if (new_msg != nullptr) {
                q.push(new_msg);
            }
        }
        GenericMsg* msg;
        bool have_command = q.try_pop(msg);
        if (have_command) {
            msg->accept_read(*this);  // esto equivale a una llamada al handle_read
        }
        for (auto& [name, player]: players) {
            stage.delete_player_from_stage(*player);  // Borro su dibujo viejo
            player->update();
            stage.draw_player(*player);
        }
        stage.update();
        stage.print();
        sleep(1);
    }
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


// OH el HORROR
// El peor codigo que escribi en este tp hasta ahora
// pero funciona
// no lo toquen
GenericMsg* GameMain::create_msg(std::string command) {
    std::map<std::string, uint8_t> command_map{
            {"a", 0x01},
            {"d", 0x02},
            {"j", 0x03},
            {"x", 0x04},
            //{"a", 0x05},
            {"w", 0x06},
            {"t", 0x07},
    };
    if (command.size() != 3) {
        return nullptr;
    }
    if (command.substr(0, 1) == "s") {
        static StartActionMsg msg;
        if (command.substr(2, 1) == "0") {
            msg.set_player_name(player_name1);
        } else if (command.substr(2, 1) == "1") {
            msg.set_player_name(player_name2);
        } else {
            return nullptr;
        }
        try {
            msg.set_action_id(command_map[command.substr(1, 1)]);
        } catch (...) {
            return nullptr;
        }
        return &msg;
    }
    if (command.substr(0, 1) == "x") {
        static StopActionMsg msg;
        if (command.substr(2, 1) == "0") {
            msg.set_player_name(player_name1);
        } else if (command.substr(2, 1) == "1") {
            msg.set_player_name(player_name2);
        } else {
            return nullptr;
        }
        try {
            msg.set_action_id(command_map[command.substr(1, 1)]);
        } catch (...) {
            return nullptr;
        }
        return &msg;
    }
    return nullptr;
}
