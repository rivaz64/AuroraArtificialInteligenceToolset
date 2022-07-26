#include "pch.h"

#include "auWorldState.h"
#include "auAction.h"
#include "auPlansGraph.h"

using auToolSeetSDK::WorldState;
using auToolSeetSDK::Action;
using auToolSeetSDK::PlansGraph;
using auToolSeetSDK::Vector;

namespace MY_CONDICIONS
{
enum E
{
ENEMY_DEAD,
HAS_WEAPON,
HAS_BULLETS,
IS_COVERED,
};
}

int main(int argc, char** argv)
{
  WorldState::defineCondicion(MY_CONDICIONS::ENEMY_DEAD);
  WorldState::defineCondicion(MY_CONDICIONS::HAS_WEAPON);
  WorldState::defineCondicion(MY_CONDICIONS::HAS_BULLETS);
  WorldState::defineCondicion(MY_CONDICIONS::IS_COVERED);
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}

class WorldStateTest : public ::testing::Test
{
  protected:
    // Objects declared here can be used by all tests in the test case for this component.
    WorldState ws;
};

TEST_F(WorldStateTest, same) {
    WorldState deadEnemy;
    deadEnemy.setCondicion(MY_CONDICIONS::ENEMY_DEAD,true);

    ws.setCondicion(MY_CONDICIONS::ENEMY_DEAD,true);
    ASSERT_TRUE(ws.satisfies(deadEnemy));
}

TEST_F(WorldStateTest, different) {
    WorldState deadEnemy;
    deadEnemy.setCondicion(MY_CONDICIONS::ENEMY_DEAD,true);

    ws.setCondicion(MY_CONDICIONS::ENEMY_DEAD,false);
    ASSERT_FALSE(ws.satisfies(deadEnemy));
}

TEST_F(WorldStateTest, equalMatters) {
    WorldState goal;
    goal.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(MY_CONDICIONS::HAS_WEAPON,false);
    goal.setCondicion(MY_CONDICIONS::IS_COVERED,false);

    ws.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(MY_CONDICIONS::HAS_WEAPON,false);
    ws.setCondicion(MY_CONDICIONS::IS_COVERED,false);
    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, nothingMatters) {
    WorldState goal;
    goal.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(MY_CONDICIONS::HAS_WEAPON,false);
    goal.setCondicion(MY_CONDICIONS::IS_COVERED,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMatters) {
    WorldState goal;
    goal.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(MY_CONDICIONS::HAS_WEAPON,false);
    goal.setCondicion(MY_CONDICIONS::IS_COVERED,false);

    ws.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMattersDifferentValues) {
    WorldState goal;
    goal.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(MY_CONDICIONS::HAS_WEAPON,false);
    goal.setCondicion(MY_CONDICIONS::IS_COVERED,false);

    ws.setCondicion(MY_CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(MY_CONDICIONS::HAS_BULLETS,true);

    ASSERT_EQ(ws.getNumOfUnsatisfiedCondicion(goal),1);
}




