#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "../../server/game_logic/game.h"

class GameResources {
public:
    // Método para acceder a la instancia única del singleton
    static GameResources& GetInstance() {
        static GameResources instance;  // Instancia única
        return instance;
    }

    bool IsResourcesLoaded() { return resourcesLoaded; }

    void LoadResources() {
        if (!resourcesLoaded) {
            std::cout << "Cargando recursos...\n";
            resourcesLoaded = true;
            sendqueue1 = new Queue<std::shared_ptr<GenericMsg>>();
            sendqueue2 = new Queue<std::shared_ptr<GenericMsg>>();
            recv_queue = new Queue<std::shared_ptr<GenericMsg>>();
            ids = std::make_shared<std::set<uint>>();
            ids->insert(1);
            ids->insert(2);
            senders.add(sendqueue1, 1);
            senders.add(sendqueue2, 2);
            player_obs = std::make_shared<PlayerObserver>(senders, ids);
            player_names = {"player1", "player2"};
            if (maps.empty()) {
                LoadMaps();
            }
        }
    }

    void freeNecesaryResources() {
        for (auto& [_, player]: players) {
            delete player;
        }
        players.clear();
        delete sendqueue1;
        delete sendqueue2;
        delete recv_queue;
        sendqueue1 = new Queue<std::shared_ptr<GenericMsg>>();
        sendqueue2 = new Queue<std::shared_ptr<GenericMsg>>();
        recv_queue = new Queue<std::shared_ptr<GenericMsg>>();
    }

    std::shared_ptr<GameLoop> UseResource(Map& map, Stage* current_stage) {
        if (!resourcesLoaded) {
            return nullptr;
        }
        std::vector<Coordinate> coordinates = map.get_players_spawn_sites();
        for (size_t i = 0; i < player_names.size(); i++) {
            players[player_names[i]] =
                    new Player(coordinates[i], i + 1, player_names[i], *player_obs.get());
        }
        return std::make_shared<GameLoop>(*recv_queue, players, false);
    }

    void KillAll() {
        if (resourcesLoaded) {
            std::cout << "Liberando todo...\n";
            resourcesLoaded = false;
            delete sendqueue1;
            delete sendqueue2;
            ids.reset();
            senders.remove_all();
            for (auto& [_, player]: players) {
                delete player;
            }
            players.clear();
            player_names.clear();
            for (auto& [_, map]: maps) {
                delete map;
            }
            maps.clear();
        }
    };

private:
    void LoadMaps() {
        std::string maps_folder_path = "tests_map";
        for (const auto& entry: std::filesystem::directory_iterator(maps_folder_path)) {
            std::string file_name = entry.path().filename().string();
            if (file_name.find(".yaml") == std::string::npos) {
                continue;
            }
            YAML::Node mapa_yaml = YAML::LoadFile(entry.path().string());
            std::string new_map_name = mapa_yaml["map_name"].as<std::string>();
            int rows = mapa_yaml["map_rows"].as<int>();
            int columns = mapa_yaml["map_columns"].as<int>();
            std::vector<Coordinate> players_spawn_sites;
            std::vector<std::tuple<Coordinate, int>> items_spawn_sites;
            std::vector<std::vector<int>> matrix;
            for (const auto& spawn: mapa_yaml["map_player_spawn_sites"]) {
                Coordinate spawn_point = Coordinate(spawn[0].as<int>(), spawn[1].as<int>());
                players_spawn_sites.push_back(spawn_point);
            }
            for (const auto& spawn: mapa_yaml["map_weapon_spawn_sites"]) {
                Coordinate spawn_point = Coordinate(spawn[0].as<int>(), spawn[1].as<int>());
                int item_id = spawn[2].as<uint>();
                items_spawn_sites.push_back(std::make_tuple(spawn_point, item_id));
            }
            for (const auto& row: mapa_yaml["map_matrix"]) {
                std::vector<int> row_vector;
                for (const auto& cell: row) {
                    row_vector.push_back(cell.as<int>());
                }
                matrix.push_back(row_vector);
            }
            Map* new_map = new Map(new_map_name, rows, columns, matrix, players_spawn_sites,
                                   items_spawn_sites);
            maps[new_map_name] = new_map;
        }
    }

    GameResources() = default;  // Constructor privado
    ~GameResources() = default;

    // Deshabilitar copia y movimiento
    GameResources(const GameResources&) = delete;
    GameResources& operator=(const GameResources&) = delete;

    bool resourcesLoaded = false;

    // Lo que se necesita y se necesita getters
    std::shared_ptr<PlayerObserver> player_obs;
    SendQueuesMonitor<std::shared_ptr<GenericMsg>> senders;
    std::shared_ptr<std::set<uint>> ids;
    Queue<std::shared_ptr<GenericMsg>>* recv_queue;
    Queue<std::shared_ptr<GenericMsg>>* sendqueue1;
    Queue<std::shared_ptr<GenericMsg>>* sendqueue2;
    std::vector<std::string> player_names;
    std::map<std::string, Player*> players;
    std::map<std::string, Map*> maps;

public:
    std::shared_ptr<PlayerObserver> GetPlayerObserver() {
        if (!resourcesLoaded) {
            return nullptr;
        }
        return player_obs;
    }

    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& GetSenders() { return std::ref(senders); }

    std::shared_ptr<std::set<uint>> GetIds() {
        if (!resourcesLoaded) {
            return nullptr;
        }
        return ids;
    }

    Queue<std::shared_ptr<GenericMsg>>& GetRecvQueue() { return std::ref(*recv_queue); }

    Queue<std::shared_ptr<GenericMsg>>& GetSendQueue1() { return std::ref(*sendqueue1); }

    Queue<std::shared_ptr<GenericMsg>>& GetSendQueue2() { return std::ref(*sendqueue2); }

    std::vector<std::string> GetPlayerNames() {
        if (!resourcesLoaded) {
            return {};
        }
        return player_names;
    }

    std::map<std::string, Player*> GetPlayers() {
        if (!resourcesLoaded) {
            return {};
        }
        return players;
    }

    std::map<std::string, Map*> GetMaps() {
        if (!resourcesLoaded) {
            return {};
        }
        return maps;
    }
};
