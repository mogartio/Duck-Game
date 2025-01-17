#include "game_loop.h"

#include <regex>
#include <tuple>
#include <vector>

#include "config/config.h"
#include "map/spawn_point.h"
#include "player/weapons/mystery_box.h"
#define TARGET_TIME 35
using namespace std::chrono;
#include "game.h"

GameLoop::GameLoop(Queue<std::shared_ptr<GenericMsg>>& q, std::map<std::string, Player*> players,
                   bool is_testing, bool is_cheating):
        receiver_q(q), is_testing(is_testing), players(players), is_cheating(is_cheating) {}

// Recibe el stage del round, devuelve el nombre del pato ganador
std::string GameLoop::play_round(Stage& stage, Map& map) {
    init_round(stage, map);
    std::string winner;
    bool round_over = false;
    while (!round_over) {
        steady_clock::time_point t0 = steady_clock::now();  // empieza el timer
        spawn_weapons();
        process_commands(stage);
        winner = look_for_dead_people_and_do_what_you_must(stage, round_over);
        steady_clock::time_point t1 = steady_clock::now();  // termina el timer!
        sleep_for_round(t0, t1);  // por suerte en fisica aprendimos como medir tiempos
    }
    return winner;
}

void GameLoop::init_round(Stage& stage, Map& map) {
    std::vector<std::tuple<Coordinate, int>> weapon_spawn_sites = map.get_items_spawn_sites();

    for (auto& weapon: weapon_spawn_sites) {
        std::shared_ptr<WeaponSpawnPoint> spawn =
                std::make_shared<WeaponSpawnPoint>(std::get<0>(weapon), stage, std::get<1>(weapon));
        weapon_spawns.push_back(spawn);
    }

    std::vector<Coordinate> box_positions = map.get_boxes_spawn_sites();
    for (auto& box_position: box_positions) {
        stage.add_box(std::make_shared<MysteryBox>(stage, box_position));
        stage.add_new_box(std::make_shared<MysteryBox>(stage, box_position));
    }

    std::vector<Coordinate> player_spawns = map.get_players_spawn_sites();
    int i = 0;
    for (auto [name, player]: players) {
        Coordinate spawn = player_spawns[i];
        player->init_for_stage(&stage, spawn);
        alive_players.insert(name);
        stage.add_player(player, player->get_id());
        i++;
    }
    for (auto [name, player]: players) {  // primero tuve que mandar todos los nombres
        player->unarm_self();
    }
}

void GameLoop::spawn_weapons() {
    for (auto& spawn: weapon_spawns) {
        spawn->update();
    }
}

void GameLoop::process_commands(Stage& stage) {
    for (int i = 0; i < 10; i++) {
        if (is_testing) {
            create_command();
            i = 10;
        }
        std::shared_ptr<GenericMsg> msg;
        if (receiver_q.try_pop(msg)) {
            msg->accept_read(*this);  // esta linea ejecuta el comando
        }
    }
    for (auto& [name, player]: players) {
        if (!player->lives()) {
            continue;
        }
        stage.delete_player_from_stage(*player);  // Borro su dibujo viejo
        player->update();
        stage.draw_player(*player);
    }
    stage.update();
    if (is_testing) {
        stage.print();
    }
}

// Se fija si solamente queda un jugador vivo. si lo hay settea el bool que se le pasa a true y
// devuelve el nombre del ganador
std::string GameLoop::look_for_dead_people_and_do_what_you_must(Stage& stage, bool& round_over) {
    std::vector<std::string> recently_deceased;  // its never been this serious
    for (std::string player: alive_players) {
        if (!players[player]->lives()) {
            recently_deceased.push_back(player);
        }
    }
    for (std::string player: recently_deceased) {
        alive_players.erase(player);
    }
    if (alive_players.size() == 0) {
        round_over = true;
        return "";
    }
    if (alive_players.size() == 1) {
        round_over = true;
        stage.delete_player_from_stage(*players[*alive_players.begin()]);  // Borro su dibujo viejo
        return *alive_players.begin();
    }
    return "";
}


// Duerme lo que le falta para terminar el ciclo actual
void GameLoop::sleep_for_round(steady_clock::time_point t0, steady_clock::time_point t1) {
    if (is_testing) {
        return;
    }
    duration<int, std::milli> time_span = duration_cast<duration<int, std::milli>>(t1 - t0);
    duration<int, std::milli> sleep_duration =
            duration<int, std::milli>(TARGET_TIME) - (time_span % TARGET_TIME);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
}

void GameLoop::cheat() {
    std::cout << "Ingresar el cheat con el siguiente formato: spawn {player_name} {weapon_id}"
              << std::endl;
    std::string command;
    std::getline(std::cin, command);
    std::istringstream iss(command);
    std::string action, player_name, weapon_id;
    if (iss >> action >> player_name >> weapon_id) {
        if (action == "spawn") {
            std::string extra;
            if (!(iss >> extra)) {
                if (players[player_name]) {
                    try {
                        int id = stoi(weapon_id);
                        players[player_name]->cheat(id);
                    } catch (...) {
                        std::cout << "Weapon_id no fue ingresado como numero o el nombre es "
                                     "incorrecto "
                                  << std::endl;
                    }
                }
            }
        }
    }
}
void GameLoop::handle_read(const StartActionMsg& msg) {
    int action = msg.get_action_id();
    if (action == 0x08) {  // codigo de CHEAT
        if (is_cheating) {
            cheat();
        }
        return;
    }
    players[msg.get_player_name()]->add_action(action);
}

void GameLoop::handle_read(const StopActionMsg& msg) {
    int action = msg.get_action_id();
    players[msg.get_player_name()]->remove_action(action);
}

void GameLoop::handle_read(const StartRoundMsg& msg) {
    // nada
}

// podes ignorar todo lo que esta abajo

// OH el HORROR
// El peor codigo que escribi en este tp hasta ahora
// pero funciona
// no lo toquen
std::shared_ptr<GenericMsg> GameLoop::create_msg(const std::string& command) {
    std::string player_name1;
    std::string player_name2;
    auto it = players.begin();
    if (it != players.end()) {
        player_name1 = it->first;
        ++it;
    }
    if (it != players.end()) {
        player_name2 = it->first;
    }
    std::map<std::string, uint8_t> command_map{
            {"a", 0x01}, {"d", 0x02}, {"j", 0x03}, {"x", 0x04}, {"w", 0x06}, {"t", 0x07},
    };
    if (command.size() != 3) {
        return nullptr;
    }
    if (command.substr(0, 1) == "s") {
        auto msg = std::make_shared<StartActionMsg>();
        if (command.substr(2, 1) == "0") {
            msg->set_player_name(player_name1);
        } else if (command.substr(2, 1) == "1") {
            msg->set_player_name(player_name2);
        } else {
            return nullptr;
        }
        try {
            msg->set_action_id(command_map.at(command.substr(1, 1)));
        } catch (...) {
            return nullptr;
        }
        return msg;
    }
    if (command.substr(0, 1) == "x") {
        auto msg = std::make_shared<StopActionMsg>();
        if (command.substr(2, 1) == "0") {
            msg->set_player_name(player_name1);
        } else if (command.substr(2, 1) == "1") {
            msg->set_player_name(player_name2);
        } else {
            return nullptr;
        }
        try {
            msg->set_action_id(command_map.at(command.substr(1, 1)));
        } catch (...) {
            return nullptr;
        }
        return msg;
    }
    return nullptr;
}

void GameLoop::create_command() {
    std::string command;
    std::getline(std::cin, command);
    std::shared_ptr<GenericMsg> new_msg = create_msg(command);
    if (new_msg != nullptr) {
        receiver_q.push(new_msg);
    }
}
