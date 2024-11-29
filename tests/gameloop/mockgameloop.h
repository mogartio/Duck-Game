#include <gtest/gtest.h>
#include "../../server/game_logic/game.h"

class GameResources {
public:
    // Método para acceder a la instancia única del singleton
    static GameResources& GetInstance() {
        static GameResources instance; // Instancia única
        return instance;
    }

    bool IsResourcesLoaded() {
        return resourcesLoaded;
    }

    void LoadResources() {
        if (!resourcesLoaded) {
            std::cout << "Cargando recursos...\n";
            resourcesLoaded = true;
            ids = std::make_shared<std::set<uint>>();
            ids->insert(1);
            ids->insert(2);
            senders.add(&sendqueue1,1);
            senders.add(&sendqueue2,2);
            player_obs = std::make_shared<PlayerObserver>(senders, ids);
            player_names = {"player1", "player2"};
        }
    }

    std::shared_ptr<GameLoop> UseResource(Map& map, Stage* current_stage) {
        LoadResources();
        std::vector<Coordinate> coordinates = map.get_players_spawn_sites();
        for (size_t i = 0; i < player_names.size(); i++) {
            players[player_names[i]] = new Player(coordinates[i], i + 1, player_names[i], *player_obs.get());
        }
        return std::make_shared<GameLoop>(recv_queue, players, true);
    }

    void UnloadResources() {
        if (resourcesLoaded) {
            std::cout << "Liberando recursos...\n";
            resourcesLoaded = false;
            ids.reset();
            senders.remove_all();
            for (auto& [_, player]: players) {
                delete player;
            }
        }
    }
private:
    GameResources() = default; // Constructor privado
    ~GameResources() = default;

    // Deshabilitar copia y movimiento
    GameResources(const GameResources&) = delete;
    GameResources& operator=(const GameResources&) = delete;

    bool resourcesLoaded = false;
    // Lo que no se necesita
    SendQueuesMonitor<std::shared_ptr<GenericMsg>> senders;
    std::shared_ptr<PlayerObserver> player_obs;

    // Lo que se necesita y se necesita getters
    MapManager map_manager;
    std::shared_ptr<std::set<uint>> ids;
    Queue<std::shared_ptr<GenericMsg>> recv_queue;
    Queue<std::shared_ptr<GenericMsg>> sendqueue1;
    Queue<std::shared_ptr<GenericMsg>> sendqueue2;
    std::vector<std::string> player_names;
    std::map<std::string, Player*> players;

public:
    MapManager& GetMapManager() {
        return std::ref(map_manager);
    }

    std::shared_ptr<std::set<uint>> GetIds() {
        if (!resourcesLoaded) {
            return nullptr;
        }
        return ids;
    }

    Queue<std::shared_ptr<GenericMsg>>& GetRecvQueue() {
        return std::ref(recv_queue);
    }

    Queue<std::shared_ptr<GenericMsg>>& GetSendQueue1() {
        return std::ref(sendqueue1);
    }

    Queue<std::shared_ptr<GenericMsg>>& GetSendQueue2() {
        return std::ref(sendqueue2);
    }

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
};
