#include <thread>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock_protocol.h"

using ::testing::_;    // Matcher para "cualquier valor".
using ::testing::Ref;  // Matcher para referencia exacta.

TEST(EverythingOkMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        EverythingOkMsg msg;
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::EVERYTHING_OK_MSG);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ErrorMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        ErrorMsg msg("Error en el envio este");
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::ERROR_MSG);
        EXPECT_EQ(dynamic_cast<ErrorMsg*>(msg.get())->get_error_msg(), "Error en el envio este");
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(InfoLobbyMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::list<DescripcionPlayer> players;
        DescripcionPlayer player;
        player.nombre = "player1";
        player.color = 1;
        player.is_ready = 1;
        players.push_back(player);
        DescripcionPlayer player2;
        player2.nombre = "player2";
        player2.color = 2;
        player2.is_ready = 0;
        players.push_back(player2);
        uint8_t max_players = 5;
        uint8_t lobby_id = 1;
        uint8_t starting_game = 0;
        InfoLobbyMsg msg(players, max_players, lobby_id, starting_game);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::INFO_LOBBY_MSG);
        InfoLobbyMsg* info_msg = dynamic_cast<InfoLobbyMsg*>(msg.get());
        std::list<DescripcionPlayer> players = info_msg->get_players();
        DescripcionPlayer player = players.front();
        EXPECT_EQ(player.nombre, "player1");
        EXPECT_EQ(player.color, 1);
        EXPECT_EQ(player.is_ready, 1);
        players.pop_front();
        player = players.front();
        EXPECT_EQ(player.nombre, "player2");
        EXPECT_EQ(player.color, 2);
        EXPECT_EQ(player.is_ready, 0);
        EXPECT_EQ(info_msg->get_max_players(), 5);
        EXPECT_EQ(info_msg->get_lobby_id(), 1);
        EXPECT_EQ(info_msg->get_starting_game(), 0);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(SendLobbiesListMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::vector<DescripcionLobby> lobbies;
        DescripcionLobby lobby;
        lobby.idLobby = 1;
        lobby.nombreLobby = "lobby1";
        lobby.cantidadJugadores = 2;
        lobby.maxJugadores = 5;
        lobbies.push_back(lobby);
        DescripcionLobby lobby2;
        lobby2.idLobby = 2;
        lobby2.nombreLobby = "lobby2";
        lobby2.cantidadJugadores = 1;
        lobby2.maxJugadores = 3;
        lobbies.push_back(lobby2);
        SendLobbiesListMsg msg(lobbies);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::SEND_LOBBIES_LIST_MSG);
        SendLobbiesListMsg* lobbies_msg = dynamic_cast<SendLobbiesListMsg*>(msg.get());
        std::vector<DescripcionLobby> lobbies = lobbies_msg->get_lobbies();
        EXPECT_EQ(lobbies.size(), 2);
        DescripcionLobby lobby = lobbies.back();
        EXPECT_EQ(lobby.idLobby, 2);
        EXPECT_EQ(lobby.nombreLobby, "lobby2");
        EXPECT_EQ(lobby.cantidadJugadores, 1);
        EXPECT_EQ(lobby.maxJugadores, 3);
        lobbies.pop_back();
        lobby = lobbies.back();
        EXPECT_EQ(lobby.idLobby, 1);
        EXPECT_EQ(lobby.nombreLobby, "lobby1");
        EXPECT_EQ(lobby.cantidadJugadores, 2);
        EXPECT_EQ(lobby.maxJugadores, 5);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(SendMapMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::vector<uint16_t> map = {1, 2, 3, 4, 5, 6};
        uint16_t filas = 2;
        uint16_t columnas = 3;
        SendMapMsg msg(map, filas, columnas, GenericMsg::Theme::DAY);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::SEND_MAP_MSG);
        SendMapMsg* map_msg = dynamic_cast<SendMapMsg*>(msg.get());
        std::vector<uint16_t> map = map_msg->get_map();
        EXPECT_EQ(map.size(), 6);
        EXPECT_EQ(map[0], 1);
        EXPECT_EQ(map[1], 2);
        EXPECT_EQ(map[2], 3);
        EXPECT_EQ(map[3], 4);
        EXPECT_EQ(map[4], 5);
        EXPECT_EQ(map[5], 6);
        EXPECT_EQ(map_msg->get_filas(), 2);
        EXPECT_EQ(map_msg->get_columnas(), 3);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(GameEndedMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        GameEndedMsg msg;
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::GAME_ENDED_MSG);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(WinnerMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        WinnerMsg msg("player1");
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::WINNER_MSG);
        WinnerMsg* winner_msg = dynamic_cast<WinnerMsg*>(msg.get());
        EXPECT_EQ(winner_msg->get_winner_name(), "player1");
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ProjectileInfoMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::vector<std::pair<uint8_t, uint8_t>> trail = {{1, 2}, {3, 4}};
        uint8_t pos_x = 5;
        uint8_t pos_y = 6;
        uint8_t item = 7;
        uint8_t facing_direction_first = 8;
        uint8_t facing_direction_second = 9;
        ProjectileInfoMsg msg(trail, pos_x, pos_y, item, facing_direction_first,
                              facing_direction_second);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::PROJECTILE_INFO_MSG);
        ProjectileInfoMsg* projectile_msg = dynamic_cast<ProjectileInfoMsg*>(msg.get());
        std::vector<std::pair<uint8_t, uint8_t>> trail = projectile_msg->get_trail();
        EXPECT_EQ(trail.size(), 2);
        EXPECT_EQ(trail[0].first, 1);
        EXPECT_EQ(trail[0].second, 2);
        EXPECT_EQ(trail[1].first, 3);
        EXPECT_EQ(trail[1].second, 4);
        EXPECT_EQ(projectile_msg->get_pos_x(), 5);
        EXPECT_EQ(projectile_msg->get_pos_y(), 6);
        EXPECT_EQ(projectile_msg->get_item(), 7);
        EXPECT_EQ(projectile_msg->get_facing_direction_first(), 8);
        EXPECT_EQ(projectile_msg->get_facing_direction_second(), 9);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(UpdatedPlayerInfoMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::string player_name = "player1";
        std::pair<uint16_t, uint16_t> position = {1, 2};
        uint8_t state = 3;
        uint8_t facing_direction = 4;
        uint8_t facing_direction_second = 5;
        UpdatedPlayerInfoMsg msg(player_name, position, state, facing_direction,
                                 facing_direction_second);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::UPDATED_PLAYER_INFO_MSG);
        UpdatedPlayerInfoMsg* updated_player_msg = dynamic_cast<UpdatedPlayerInfoMsg*>(msg.get());
        EXPECT_EQ(updated_player_msg->get_player_name(), "player1");
        std::pair<uint16_t, uint16_t> position = updated_player_msg->get_position();
        EXPECT_EQ(position.first, 1);
        EXPECT_EQ(position.second, 2);
        EXPECT_EQ(updated_player_msg->get_state(), 3);
        EXPECT_EQ(updated_player_msg->get_facing_direction(), 4);
        EXPECT_EQ(updated_player_msg->get_facing_direction_second(), 5);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(PickupDropMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        uint8_t item_id = 1;
        std::string player_name = "player1";
        PickupDropMsg msg(player_name, item_id);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::PICKUP_DROP_MSG);
        PickupDropMsg* pickup_msg = dynamic_cast<PickupDropMsg*>(msg.get());
        EXPECT_EQ(pickup_msg->get_item_id(), 1);
        EXPECT_EQ(pickup_msg->get_player_name(), "player1");
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(PlayerInfoMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::string player_name = "player1";
        uint8_t color = 1;
        PlayerInfoMsg msg(player_name, color);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::PLAYER_INFO_MSG);
        PlayerInfoMsg* player_msg = dynamic_cast<PlayerInfoMsg*>(msg.get());
        EXPECT_EQ(player_msg->get_player_name(), "player1");
        EXPECT_EQ(player_msg->get_color(), 1);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(NotProyectileInfo, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        uint8_t item = 1;
        std::pair<uint8_t, uint8_t> position_x_y = {2, 3};
        NotProyectileInfo msg(item, position_x_y);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::NOT_PROJECTILE_INFO);
        NotProyectileInfo* not_proyectile_msg = dynamic_cast<NotProyectileInfo*>(msg.get());
        EXPECT_EQ(not_proyectile_msg->get_item(), 1);
        std::pair<uint8_t, uint8_t> position_x_y = not_proyectile_msg->get_position_x_y();
        EXPECT_EQ(position_x_y.first, 2);
        EXPECT_EQ(position_x_y.second, 3);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ShootMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::string player_name = "player1";
        std::pair<uint8_t, uint8_t> position_x_y = {1, 2};
        ShootMsg msg(player_name, position_x_y);
        msg.accept_send(server);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::shared_ptr<GenericMsg> msg = client.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::SHOOT_MSG);
        ShootMsg* shoot_msg = dynamic_cast<ShootMsg*>(msg.get());
        EXPECT_EQ(shoot_msg->get_player_name(), "player1");
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ViewLobbiesMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::VIEW_LOBBIES_MSG);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        ViewLobbiesMsg msg;
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ChooseLobbyMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::CHOOSE_LOBBY_MSG);
        ChooseLobbyMsg* choose_lobby_msg = dynamic_cast<ChooseLobbyMsg*>(msg.get());
        EXPECT_EQ(choose_lobby_msg->get_lobby_id(), 1);
        EXPECT_EQ(choose_lobby_msg->get_player_name(), "player1");
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        uint8_t lobby_id = 1;
        std::string player_name = "player1";
        ChooseLobbyMsg msg(lobby_id, player_name);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(CreateLobbyMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::CREATE_LOBBY_MSG);
        CreateLobbyMsg* create_lobby_msg = dynamic_cast<CreateLobbyMsg*>(msg.get());
        EXPECT_EQ(create_lobby_msg->get_player_name(), "player1");
        EXPECT_EQ(create_lobby_msg->get_lobby_name(), "lobby1");
        EXPECT_EQ(create_lobby_msg->get_max_players(), 5);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::string player_name = "player1";
        std::string lobby_name = "lobby1";
        uint8_t max_players = 5;
        CreateLobbyMsg msg(player_name, lobby_name, max_players);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(GoBackMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::GO_BACK_MSG);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        GoBackMsg msg;
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(ExitFromLobbyMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::EXIT_FROM_LOBBY_MSG);
        ExitFromLobbyMsg* exit_from_lobby_msg = dynamic_cast<ExitFromLobbyMsg*>(msg.get());
        EXPECT_EQ(exit_from_lobby_msg->get_player_name(), "player1");
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::string player_name = "player1";
        ExitFromLobbyMsg msg(player_name);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(StartGameMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::START_GAME_MSG);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        StartGameMsg msg;
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(CustomizedPlayerInfoMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::LOBBY_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::CUSTOMIZED_PLAYER_INFO_MSG);
        CustomizedPlayerInfoMsg* customized_player_info_msg =
                dynamic_cast<CustomizedPlayerInfoMsg*>(msg.get());
        EXPECT_EQ(customized_player_info_msg->get_lobby_id(), 1);
        EXPECT_EQ(customized_player_info_msg->get_color(), 2);
        EXPECT_EQ(customized_player_info_msg->get_player_name(), "player1");
        EXPECT_EQ(customized_player_info_msg->get_player_new_name(), "player2");
        EXPECT_EQ(customized_player_info_msg->get_is_ready(), 0);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        uint8_t lobby_id = 1;
        uint8_t color = 2;
        std::string player_name = "player1";
        std::string player_new_name = "player2";
        uint8_t is_ready = 0;
        CustomizedPlayerInfoMsg msg(lobby_id, color, player_name, player_new_name, is_ready);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(StartActionMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::START_ACTION_MSG);
        StartActionMsg* start_action_msg = dynamic_cast<StartActionMsg*>(msg.get());
        EXPECT_EQ(start_action_msg->get_player_name(), "player1");
        EXPECT_EQ(start_action_msg->get_action_id(), 1);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::string player_name = "player1";
        uint8_t action = 1;
        StartActionMsg msg(action, player_name);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}

TEST(StopActionMsg, CallsItInComunicationSystem) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        ServerProtocol server(skt_client);
        std::shared_ptr<GenericMsg> msg = server.receive();
        EXPECT_EQ(msg->get_type(), GenericMsg::Type::GAME_MSG);
        EXPECT_EQ(msg->get_header(), GenericMsg::STOP_ACTION_MSG);
        StopActionMsg* stop_action_msg = dynamic_cast<StopActionMsg*>(msg.get());
        EXPECT_EQ(stop_action_msg->get_player_name(), "player1");
        EXPECT_EQ(stop_action_msg->get_action_id(), 1);
    };

    auto thread_client = []() {
        Socket socket("localhost", "8080");
        ClientProtocol client(socket);
        std::string player_name = "player1";
        uint8_t action = 1;
        StopActionMsg msg(action, player_name);
        msg.accept_send(client);
    };

    std::thread server_thread(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client_thread(thread_client);

    server_thread.join();
    client_thread.join();
}
