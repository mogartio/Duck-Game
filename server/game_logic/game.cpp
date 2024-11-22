#include "game.h"

Game::Game(Queue<std::shared_ptr<GenericMsg>>& recv, const std::vector<std::string>& player_names,
           bool is_testing, SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders,
           std::shared_ptr<std::set<uint>> ids):
        senders(senders), recv(recv), player_names(player_names), ids(ids), game_over(false), is_testing(is_testing), players_created(false), map_manager() {

}

std::map<std::string, Player*> Game::generate_players(const std::vector<std::string>& names,
                                                      const PlayerObserver& obs, Map& map) {
    std::vector<Coordinate> coordinates = map.get_players_spawn_sites();
    for (size_t i = 0; i < names.size(); i++) {
        players[names[i]] = new Player(coordinates[i], i + 1, names[i], obs);
        player_points[names[i]] = 0;
    }
    return players;
}

void Game::run() {
    while (!game_over) {
        for (int i = 0; i < Config::get_instance()->rounds_per_cycle; i++) {

            Map& map = map_manager.get_random_map();
            current_stage = new Stage(map, senders, ids);
            send_map(map);
        
            const PlayerObserver* player_obs = new PlayerObserver(senders, ids);
            players = generate_players(player_names, *player_obs, map);
            game_loop = std::make_shared<GameMain>(recv, players, is_testing);

            std::string winner = game_loop->play_round(*current_stage, map);
            player_points[winner]++;

            delete current_stage;
        }
        for (auto& [name, points]: player_points) {
            if (points >= 5) {
                game_over = true;
            }
        }
    }
    std::shared_ptr<GenericMsg> msg = std::make_shared<GameEndedMsg>();
    senders.broadcast(msg);
}

void Game::send_map(Map& map) {
    std::vector<uint16_t> map_vector = current_stage->get_vector_representation();
    std::shared_ptr<SendMapMsg> map_msg = std::make_shared<SendMapMsg>(
            map_vector, map.get_rows(), map.get_columns());
    std::list<std::shared_ptr<GenericMsg>> dejenmepasarleunmensajedirectoporfavor;
    dejenmepasarleunmensajedirectoporfavor.push_back(map_msg);
    senders.broadcast(dejenmepasarleunmensajedirectoporfavor);
}
