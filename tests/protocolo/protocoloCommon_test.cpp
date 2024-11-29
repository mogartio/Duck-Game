#include <thread>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock_protocol.h"

using ::testing::_;    // Matcher para "cualquier valor".
using ::testing::Ref;  // Matcher para referencia exacta.

TEST(InfoLobbyMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    InfoLobbyMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const InfoLobbyMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<InfoLobbyMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(CustomizedPlayerInfoMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    CustomizedPlayerInfoMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const CustomizedPlayerInfoMsg&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<CustomizedPlayerInfoMsg&>()))
            .Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ViewLobbiesMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ViewLobbiesMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ViewLobbiesMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ViewLobbiesMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ChooseLobbyMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ChooseLobbyMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ChooseLobbyMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ChooseLobbyMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(CreateLobbyMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    CreateLobbyMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const CreateLobbyMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<CreateLobbyMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(GoBackMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    GoBackMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const GoBackMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<GoBackMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ExitFromLobbyMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ExitFromLobbyMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ExitFromLobbyMsg&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ExitFromLobbyMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(StartGameMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    StartGameMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const StartGameMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<StartGameMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(PlayerInfoMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    PlayerInfoMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const PlayerInfoMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<PlayerInfoMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(PickupDropMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    PickupDropMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const PickupDropMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<PickupDropMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(StartActionMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    StartActionMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const StartActionMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<StartActionMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(StopActionMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    StopActionMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const StopActionMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<StopActionMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(SendLobbiesListMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    SendLobbiesListMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const SendLobbiesListMsg&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<SendLobbiesListMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(EverythingOkMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    EverythingOkMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const EverythingOkMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<EverythingOkMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ErrorMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ErrorMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ErrorMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ErrorMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(SendMapMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    SendMapMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const SendMapMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<SendMapMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(GameEndedMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    GameEndedMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const GameEndedMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<GameEndedMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(WinnerMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    WinnerMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const WinnerMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<WinnerMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(UpdatedPlayerInfoMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    UpdatedPlayerInfoMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const UpdatedPlayerInfoMsg&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<UpdatedPlayerInfoMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ProjectileInfoMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ProjectileInfoMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ProjectileInfoMsg&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ProjectileInfoMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(NotProyectileInfoTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    NotProyectileInfo msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const NotProyectileInfo&>()))
            .Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<NotProyectileInfo&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(ShootMsgTest, CallsItOnProtocoloCommon) {
    Socket socket("8080");
    MockProtocoloCommon mockProtocoloCommon(socket);
    ShootMsg msg;

    EXPECT_CALL(mockProtocoloCommon, handle_send(::testing::An<const ShootMsg&>())).Times(1);
    EXPECT_CALL(mockProtocoloCommon, handle_recv(::testing::An<ShootMsg&>())).Times(1);

    msg.accept_send(mockProtocoloCommon);
    msg.accept_recv(mockProtocoloCommon);
}

TEST(SendUint8, SocketProtocoloCommon) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        MockProtocoloCommon mockProtocoloCommonServer(skt_client);
        uint8_t data = mockProtocoloCommonServer.recv_u_int8_t();
        EXPECT_EQ(data, 5);
        mockProtocoloCommonServer.send_u_int8_t(data);
    };
    auto thread_client = []() {
        Socket socket("localhost", "8080");
        MockProtocoloCommon mockProtocoloCommonClient(socket);
        uint8_t data = 5;
        mockProtocoloCommonClient.send_u_int8_t(data);
        uint8_t data_recv = mockProtocoloCommonClient.recv_u_int8_t();
        EXPECT_EQ(data, data_recv);
    };

    std::thread server(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client(thread_client);

    server.join();
    client.join();
    EXPECT_TRUE(true);
}

TEST(SendUint16, SocketProtocoloCommon) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        MockProtocoloCommon mockProtocoloCommonServer(skt_client);
        uint16_t data = mockProtocoloCommonServer.recv_u_int16_t();
        EXPECT_EQ(data, 5);
        mockProtocoloCommonServer.send_u_int16_t(data);
    };
    auto thread_client = []() {
        Socket socket("localhost", "8080");
        MockProtocoloCommon mockProtocoloCommonClient(socket);
        uint16_t data = 5;
        mockProtocoloCommonClient.send_u_int16_t(data);
        uint16_t data_recv = mockProtocoloCommonClient.recv_u_int16_t();
        EXPECT_EQ(data, data_recv);
    };

    std::thread server(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client(thread_client);

    server.join();
    client.join();
    EXPECT_TRUE(true);
}

TEST(SendString, SocketProtocoloCommon) {
    auto thread_server = []() {
        Socket socket("8080");
        Socket skt_client = socket.accept();
        MockProtocoloCommon mockProtocoloCommonServer(skt_client);
        std::string data = mockProtocoloCommonServer.recv_string();
        EXPECT_EQ(data, "hola");
        mockProtocoloCommonServer.send_string(data);
    };
    auto thread_client = []() {
        Socket socket("localhost", "8080");
        MockProtocoloCommon mockProtocoloCommonClient(socket);
        std::string data = "hola";
        mockProtocoloCommonClient.send_string(data);
        std::string data_recv = mockProtocoloCommonClient.recv_string();
        EXPECT_EQ(data, data_recv);
    };

    std::thread server(thread_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread client(thread_client);

    server.join();
    client.join();
    EXPECT_TRUE(true);
}
