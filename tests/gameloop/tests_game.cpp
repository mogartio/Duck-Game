#include <gtest/gtest.h>
#include "mockgameloop.h"

TEST(GameResources, test_persistance_resources) {
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), false);
    GameResources::GetInstance().LoadResources();
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), true);
}

TEST(GameResources, test_persistance_resources2) {
    EXPECT_EQ(GameResources::GetInstance().IsResourcesLoaded(), true);
}
