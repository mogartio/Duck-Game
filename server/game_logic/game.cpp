#include "game.h"

Game::Game(Queue<GenericMsg*>& recv, std::vector<std::string>& player_names, bool is_testing,
           SendQueuesMonitor<GenericMsg*>& senders):
        senders(senders), game_over(false) {
    PlayerObserver* player_obs = new PlayerObserver(senders);
    players = generate_players(player_names, *player_obs);
    game_loop = std::make_unique<GameMain>(recv, players, is_testing, senders);
}

std::map<std::string, Player*> Game::generate_players(std::vector<std::string>& names,
                                                      PlayerObserver& obs) {
    std::vector<std::tuple<int, int>> coordinates = Config::get_instance()->player_spawn_sites;
    for (size_t i = 0; i < names.size(); i++) {
        Coordinate coordinate(std::get<0>(coordinates[i]), std::get<1>(coordinates[i]));
        players[names[i]] = new Player(coordinate, i + 1, names[i], obs);
        player_points[names[i]] = 0;
    }
    return players;
}

void Game::run() {
    while (!game_over) {
        for (int i = 0; i < Config::get_instance()->rounds_per_cycle; i++) {
            current_stage = new Stage("main_map.csv", senders);
            send_map();
            std::string winner = game_loop->play_round(*current_stage);
            player_points[winner]++;
        }
        for (auto [name, points]: player_points) {
            if (points >= 5) {
                game_over = true;
            }
        }
    }
}

void Game::send_map() {
    std::vector<uint16_t> map = current_stage->get_vector_representation();
    SendMapMsg* map_msg = new SendMapMsg(map, Config::get_instance()->rows_map,
                                         Config::get_instance()->columns_map);
    std::list<GenericMsg*> dejenmepasarleunmensajedirectoporfavor;
    dejenmepasarleunmensajedirectoporfavor.push_back(map_msg);
    senders.broadcast(dejenmepasarleunmensajedirectoporfavor);
}
