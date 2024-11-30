#include <gtest/gtest.h>

#include "mockgameloop.h"

TEST(GameResources, test_persistance_resources) {
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), false);
    GameResources::GetInstance().LoadResources();
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), true);
}

using namespace ActionsId;
TEST(GameResources, test_movement_players) {
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), true);
    GameResources::GetInstance().LoadResources();
    // Obtencion de recursos
    Queue<std::shared_ptr<GenericMsg>>& recv_queue = GameResources::GetInstance().GetRecvQueue();
    // std::shared_ptr<PlayerObserver> player_obs =
    // GameResources::GetInstance().GetPlayerObserver();

    // Creacion de un nuevo juego
    auto thread_loop = []() {
        std::map<std::string, Map*> maps = GameResources::GetInstance().GetMaps();
        SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders =
                GameResources::GetInstance().GetSenders();
        std::shared_ptr<std::set<uint>> ids = GameResources::GetInstance().GetIds();
        EXPECT_NE(ids, nullptr);
        Map* map = maps["test1"];
        EXPECT_NE(map, nullptr);
        Stage* current_stage = new Stage(*map, senders, ids);
        EXPECT_NE(current_stage, nullptr);
        std::shared_ptr<GameLoop> resources =
                GameResources::GetInstance().UseResource(*map, current_stage);
        EXPECT_NE(resources, nullptr);
        resources->play_round(*current_stage, *map);
    };
    std::thread game_thread(thread_loop);


    std::this_thread::sleep_for(std::chrono::milliseconds(20));  // Espera para que se cree el juego
    // Verificacion de la creacion de los jugadores
    std::map<std::string, Player*> players = GameResources::GetInstance().GetPlayers();
    EXPECT_EQ(players.size(), 2);
    EXPECT_EQ(players["player1"]->get_id(), 1);
    EXPECT_EQ(players["player2"]->get_id(), 2);

    // Verificacion que el player1 se mueva a la izquierda
    Coordinate player1_pos = players["player1"]->get_position();
    std::shared_ptr<GenericMsg> msg =
            std::make_shared<StartActionMsg>(ActionId::MOVE_LEFT, "player1");
    std::shared_ptr<GenericMsg> msg2 =
            std::make_shared<StopActionMsg>(ActionId::MOVE_LEFT, "player1");
    recv_queue.push(msg);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    recv_queue.push(msg2);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    Coordinate player1_new_pos = players["player1"]->get_position();
    EXPECT_EQ(player1_pos.x - 1, player1_new_pos.x);
    EXPECT_TRUE(player1_pos.y == player1_new_pos.y);

    // Verificacion que el player2 se mueva a la derecha
    Coordinate player2_pos = players["player2"]->get_position();
    std::shared_ptr<GenericMsg> msg3 =
            std::make_shared<StartActionMsg>(ActionId::MOVE_RIGHT, "player2");
    std::shared_ptr<GenericMsg> msg4 =
            std::make_shared<StopActionMsg>(ActionId::MOVE_RIGHT, "player2");
    recv_queue.push(msg3);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    recv_queue.push(msg4);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    Coordinate player2_new_pos = players["player2"]->get_position();
    EXPECT_EQ(player2_pos.x + 1, player2_new_pos.x);

    // Verificacion que el player1 pueda saltar
    player1_pos = players["player1"]->get_position();
    std::shared_ptr<GenericMsg> msg5 = std::make_shared<StartActionMsg>(ActionId::JUMP, "player1");
    std::shared_ptr<GenericMsg> msg6 = std::make_shared<StopActionMsg>(ActionId::JUMP, "player1");
    recv_queue.push(msg5);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    recv_queue.push(msg6);
    std::this_thread::sleep_for(
            std::chrono::milliseconds(20));  // Espera para que se mueva el jugador
    player1_new_pos = players["player1"]->get_position();
    EXPECT_EQ(player1_pos.x, player1_new_pos.x);
    EXPECT_EQ(player1_pos.y - 2, player1_new_pos.y);

    // Mato al jugador 1 para que termine la partida
    EXPECT_FALSE(
            players["player1"]->has_chest());  // Verifico que el jugador 1 no tenia nada equipado
    EXPECT_FALSE(
            players["player1"]->has_helmet());  // Verifico que el jugador 1 no tenia nada equipado
    players["player1"]->die();
    EXPECT_FALSE(players["player1"]->lives());  // Verifico que el jugador 1 haya muerto
    EXPECT_FALSE(
            players["player1"]->has_chest());  // Verifico que el jugador 1 no tenia nada equipado
    EXPECT_FALSE(
            players["player1"]->has_helmet());  // Verifico que el jugador 1 no tenia nada equipado
    game_thread.join();
    GameResources::GetInstance().freeNecesaryResources();
}
