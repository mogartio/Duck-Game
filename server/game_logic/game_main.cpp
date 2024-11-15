#include "game_main.h"

#include <tuple>
#include <vector>

#include "config/config.h"
#include "map/spawn_point.h"
#define TARGET_TIME 35
using namespace std::chrono;

GameMain::GameMain(Queue<GenericMsg*>& q, std::map<std::string, Player*> players, bool is_testing,
                   SendQueuesMonitor<GenericMsg*>& senders):
        receiver_q(q), is_testing(is_testing), players(players), senders(senders) {}

// Recibe el stage del round, devuelve el nombre del pato ganador
std::string GameMain::play_round(Stage& stage) {
    init_round(stage);
    std::string winner;
    bool round_over = false;
    while (!round_over) {
        steady_clock::time_point t0 = steady_clock::now();  // empieza el timer
        process_commands(stage);
        winner = look_for_dead_people_and_do_what_you_must(stage, round_over);
        steady_clock::time_point t1 = steady_clock::now();  // termina el timer!
        sleep_for_round(t0, t1);  // por suerte en fisica aprendimos como medir tiempos
    }
    return winner;
}

void GameMain::init_round(Stage& stage) {
    std::vector<std::tuple<int, int>> weapon_spawn_sites =
            Config::get_instance()->weapon_spawn_sites;

    Coordinate weapon_spawn(std::get<0>(weapon_spawn_sites[0]), std::get<1>(weapon_spawn_sites[0]));
    WeaponSpawnPoint spawn(weapon_spawn, stage);
    spawn.spawn_weapon();
    for (auto [name, player]: players) {
        player->init_for_stage(&stage);
        alive_players.insert(name);
        stage.add_player(player, player->get_id());
    }
    for (auto [name, player]: players) {  // I'll do it again
        player->unarm_self();  // la sangre derramada por este doble loop pesara en la consciencia
                               // de facu
    }
}

void GameMain::process_commands(Stage& stage) {
    for (int i = 0; i < 10; i++) {
        if (is_testing) {
            create_command();
        }
        GenericMsg* msg;
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
std::string GameMain::look_for_dead_people_and_do_what_you_must(Stage& stage, bool& round_over) {
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
        std::cout << "SE TERMINO LA RONDA Y LA GANO: " << *alive_players.begin() << std::endl;
        stage.delete_player_from_stage(*players[*alive_players.begin()]);  // Borro su dibujo viejo
        return *alive_players.begin();
    }
    return "";
}


// Duerme lo que le falta para terminar el ciclo actual
void GameMain::sleep_for_round(steady_clock::time_point t0, steady_clock::time_point t1) {
    duration<int, std::milli> time_span = duration_cast<duration<int, std::milli>>(t1 - t0);
    duration<int, std::milli> sleep_duration =
            duration<int, std::milli>(TARGET_TIME) - (time_span % TARGET_TIME);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
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

// podes ignorar todo lo que esta abajo

// OH el HORROR
// El peor codigo que escribi en este tp hasta ahora
// pero funciona
// no lo toquen
GenericMsg* GameMain::create_msg(std::string command) {
    // Lo hice todavia mas feo somehow
    // its never been this serious
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

void GameMain::create_command() {
    std::string command;
    std::getline(std::cin, command);
    GenericMsg* new_msg = create_msg(command);
    if (new_msg != nullptr) {
        receiver_q.push(new_msg);
    }
}
