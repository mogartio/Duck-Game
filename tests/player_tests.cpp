#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../server/game_logic/stage.h"
#include "../server/game_logic/player/player.h"
using ::testing::Return;
#define INITIAL_X 10
#define INITIAL_Y 9

class MockStage : public Stage{
public:
    MockStage(): Stage("main_map.csv"){};
    MOCK_METHOD(void, draw_player, ());
    MOCK_METHOD(bool, is_valid_position, (Player&, Coordinate));
    MOCK_METHOD(void, delete_player_from_stage, ());
    MOCK_METHOD(void, print, ());
    MOCK_METHOD(bool, should_fall, (Player&));
};

class PlayerTest : public testing::Test {
protected:
    Coordinate initial_coordinate;
    testing::NiceMock<MockStage> stage;
    Player player;
    PlayerTest():initial_coordinate(INITIAL_X,INITIAL_Y),player(this->initial_coordinate, stage){};
};

TEST_F(PlayerTest, PlayerExists) {
    EXPECT_CALL(stage, is_valid_position(::testing::_, ::testing::_))
        .WillRepeatedly(Return(true));
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "La posicion inicial del jugador es erronea";
    ASSERT_EQ(player.get_position().y, INITIAL_Y) << "La posicion inicial del jugador es erronea";
}

TEST_F(PlayerTest, PlayerMovesHorizontallyGrounded){
    EXPECT_CALL(stage, is_valid_position(::testing::_, ::testing::_))
        .WillRepeatedly(Return(true));
    std::string right = "d";
    std::string left = "a";
    for (int i=0; i < 5; i++){
        player.move(right);
        ASSERT_EQ(player.get_position().x, INITIAL_X + i + 1) << "No se mueve a la derecha";
        ASSERT_EQ(player.get_position().y, INITIAL_Y) << "Se mueve verticalmente cuando deberia hacerlo solo a la derecha";
    }
    for (int i=0; i < 5; i++){
        player.move(left);
        ASSERT_EQ(player.get_position().x, INITIAL_X - i + 4) << "No se mueve a la izquierda";
        ASSERT_EQ(player.get_position().y, INITIAL_Y) << "Se mueve verticalmente cuando deberia hacerlo solo a la derecha";
    }
}

TEST_F(PlayerTest, PlayerJump){
    EXPECT_CALL(stage, is_valid_position(::testing::_, ::testing::_))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(stage, should_fall(::testing::_))
        .WillRepeatedly(Return(true));
    std::string jump = "w";
    std::string nothing = "s";
    player.move(jump);
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y - 2) << "No se mueve para arriba";
    player.move(nothing);
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y - 4) << "No se mueve para arriba";
    player.move(nothing);
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y - 6) << "No se mueve para arriba";
    player.move(nothing);
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y - 5) << "No cae";
    player.move(nothing);
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y - 3) << "No cae";
}

TEST_F(PlayerTest, PlayerFall){
    EXPECT_CALL(stage, is_valid_position(::testing::_, ::testing::_))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(stage, should_fall(::testing::_))
        .WillRepeatedly(Return(true));
    std::string nothing = "s";
    std::string left = "a";
    std::string jump = "w";
    player.move(nothing); //deberia cambiar el estado
    player.move(nothing); //deberia empezar a caer
    ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y +1) << "No se mueve para abajo";
    player.move(left);
    ASSERT_EQ(player.get_position().x, INITIAL_X - 1) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y + 3) << "No se mueve para abajo";
    player.move(jump);
    ASSERT_EQ(player.get_position().x, INITIAL_X - 1) << "Se mueve horizontalmente cuando deberia hacerlo solo para arriba";
    ASSERT_EQ(player.get_position().y, INITIAL_Y + 4) << "No ralentiza su caida";
}

TEST_F(PlayerTest, PlayerInvalidMovements){
    std::vector<std::string> directions{"s", "a", "w", "d"};
    for (int i=0; i < 15; i++){
        player.move(directions[i % 4]);
        ASSERT_EQ(player.get_position().x, INITIAL_X) << "Se mueve x";
        ASSERT_EQ(player.get_position().y, INITIAL_Y) << "se mueve y";
    }
}
int main (int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

