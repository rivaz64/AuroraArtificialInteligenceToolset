#include "pch.h"

#include "auWorldState.h"
#include "auAction.h"
#include "auPlansGraph.h"

using auToolSeetSDK::WorldState;
using auToolSeetSDK::Action;
using auToolSeetSDK::PlansGraph;
using auToolSeetSDK::Vector;

namespace CONDICIONS
{
enum E
{
ENEMY_DEAD,
ENEMY_IN_SIGHT,
ENEMY_IN_RANGE,
ENEMY_IN_CLOSE_RANGE,
HAS_KNIFE,
HAS_GUN,
GUN_PREPARED,
GUN_LOADED,
HAS_BULLETS,
IS_COVERED,
KNIFE_PREPARED,
WEAPON_IN_HAND,
ME_DEAD
};
}

Vector<Action> actions;

void 
defineCondicions()
{
  WorldState::defineCondicion(CONDICIONS::ENEMY_DEAD);
  WorldState::defineCondicion(CONDICIONS::ENEMY_IN_SIGHT);
  WorldState::defineCondicion(CONDICIONS::ENEMY_IN_RANGE);
  WorldState::defineCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE);
  WorldState::defineCondicion(CONDICIONS::HAS_KNIFE);
  WorldState::defineCondicion(CONDICIONS::HAS_GUN);
  WorldState::defineCondicion(CONDICIONS::GUN_PREPARED);
  WorldState::defineCondicion(CONDICIONS::GUN_LOADED);
  WorldState::defineCondicion(CONDICIONS::HAS_BULLETS);
  WorldState::defineCondicion(CONDICIONS::IS_COVERED);
  WorldState::defineCondicion(CONDICIONS::KNIFE_PREPARED);
  WorldState::defineCondicion(CONDICIONS::WEAPON_IN_HAND);
  WorldState::defineCondicion(CONDICIONS::ME_DEAD);
}

void
createActions()
{
  Action patrol(250);
  patrol.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  patrol.setPrecondicion(CONDICIONS::WEAPON_IN_HAND,true);
  patrol.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT,true);
  actions.push_back(patrol);

  Action run(150);
  run.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  run.setPrecondicion(CONDICIONS::WEAPON_IN_HAND,true);
  run.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT,true);
  actions.push_back(run);

  Action aproach(2);
  aproach.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  aproach.setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  aproach.setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, false);
  aproach.setPrecondicion(CONDICIONS::GUN_LOADED, true);
  aproach.setEffect(CONDICIONS::ENEMY_IN_RANGE, true);
  actions.push_back(aproach);

  Action aproachClose(4);
  aproach.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  aproach.setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  aproach.setPrecondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE, false);
  aproach.setEffect(CONDICIONS::ENEMY_IN_CLOSE_RANGE, true);
  actions.push_back(aproachClose);

  Action loadGun(2);
  loadGun.setPrecondicion(CONDICIONS::HAS_BULLETS, true);
  loadGun.setPrecondicion(CONDICIONS::GUN_LOADED, false);
  loadGun.setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  loadGun.setEffect(CONDICIONS::GUN_LOADED, true);
  loadGun.setEffect(CONDICIONS::HAS_BULLETS, false);
  actions.push_back(loadGun);

  Action prepareGun(1);
  prepareGun.setPrecondicion(CONDICIONS::HAS_GUN, true);
  prepareGun.setPrecondicion(CONDICIONS::WEAPON_IN_HAND, false);
  prepareGun.setPrecondicion(CONDICIONS::GUN_PREPARED, false);
  prepareGun.setEffect(CONDICIONS::WEAPON_IN_HAND, true);
  prepareGun.setEffect(CONDICIONS::GUN_PREPARED, true);
  actions.push_back(prepareGun);

  Action putAwayGun(1);
  putAwayGun.setPrecondicion(CONDICIONS::WEAPON_IN_HAND, true);
  putAwayGun.setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  putAwayGun.setEffect(CONDICIONS::GUN_PREPARED, false);
  putAwayGun.setEffect(CONDICIONS::WEAPON_IN_HAND, false);
  actions.push_back(putAwayGun);

  Action prepareKnife(1);
  prepareKnife.setPrecondicion(CONDICIONS::HAS_KNIFE, true);
  prepareKnife.setPrecondicion(CONDICIONS::WEAPON_IN_HAND, false);
  prepareKnife.setPrecondicion(CONDICIONS::KNIFE_PREPARED, false);
  prepareKnife.setEffect(CONDICIONS::KNIFE_PREPARED, true);
  prepareKnife.setEffect(CONDICIONS::WEAPON_IN_HAND, true);
  actions.push_back(prepareKnife);

  Action putAwayKnife(1);
  putAwayKnife.setPrecondicion(CONDICIONS::KNIFE_PREPARED, true);
  putAwayKnife.setPrecondicion(CONDICIONS::WEAPON_IN_HAND, true);
  putAwayKnife.setEffect(CONDICIONS::WEAPON_IN_HAND, false);
  putAwayKnife.setEffect(CONDICIONS::KNIFE_PREPARED, false);
  actions.push_back(putAwayKnife);

  Action shoot(3);
  shoot.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  shoot.setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  shoot.setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  shoot.setPrecondicion(CONDICIONS::GUN_LOADED, true);
  shoot.setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, true);
  shoot.setEffect(CONDICIONS::ENEMY_DEAD, true);
  actions.push_back(shoot);

  Action stab(3);
  stab.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  stab.setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  stab.setPrecondicion(CONDICIONS::KNIFE_PREPARED, true);
  stab.setPrecondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE, true);
  stab.setEffect(CONDICIONS::ENEMY_DEAD, true);
  actions.push_back(stab);

  Action suicide(30);
  suicide.setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  suicide.setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  suicide.setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, true);
  suicide.setEffect(CONDICIONS::ENEMY_DEAD, true);
  suicide.setEffect(CONDICIONS::ME_DEAD, true);
  actions.push_back(suicide);
}

int main(int argc, char** argv)
{
  defineCondicions();
  createActions();
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}

class WorldStateTest : public ::testing::Test
{
  protected:
    WorldState ws;
};

class ActionTest : public ::testing::Test
{
  protected:
    Action act;
};

TEST_F(WorldStateTest, same) {
    WorldState deadEnemy;
    deadEnemy.setCondicion(CONDICIONS::ENEMY_DEAD,true);

    ws.setCondicion(CONDICIONS::ENEMY_DEAD,true);
    ASSERT_TRUE(ws.satisfies(deadEnemy));
}

TEST_F(WorldStateTest, different) {
    WorldState deadEnemy;
    deadEnemy.setCondicion(CONDICIONS::ENEMY_DEAD,true);

    ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
    ASSERT_FALSE(ws.satisfies(deadEnemy));
}

TEST_F(WorldStateTest, equalMatters) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::IS_COVERED,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(CONDICIONS::HAS_GUN,false);
    ws.setCondicion(CONDICIONS::IS_COVERED,false);
    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, nothingMatters) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::IS_COVERED,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMatters) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::IS_COVERED,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMattersDifferentValues) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::IS_COVERED,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(CONDICIONS::HAS_GUN,true);

    ASSERT_EQ(ws.getNumOfUnsatisfiedCondicion(goal),1);
}

TEST_F(ActionTest, canDoAction) {
  act.setPrecondicion(CONDICIONS::HAS_GUN,true);
  act.setPrecondicion(CONDICIONS::IS_COVERED,false);

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::IS_COVERED,false);

  ASSERT_TRUE(act.validatePrecondicions(ws));
}

TEST_F(ActionTest, cantDoAction) {
  act.setPrecondicion(CONDICIONS::HAS_GUN,true);
  act.setPrecondicion(CONDICIONS::IS_COVERED,true);

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::IS_COVERED,false);

  ASSERT_FALSE(act.validatePrecondicions(ws));
}

TEST_F(ActionTest, noEffects) {

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::IS_COVERED,false);

  auto prevWS = ws;
  act.applyEffects(ws);

  ASSERT_EQ(prevWS,ws);
}

TEST_F(ActionTest, wsAfected) {

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::IS_COVERED,false);

  WorldState finalws;
  finalws.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  finalws.setCondicion(CONDICIONS::HAS_GUN,true);
  finalws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  finalws.setCondicion(CONDICIONS::IS_COVERED,false);

  act.setPrecondicion(CONDICIONS::ENEMY_DEAD,false);
  act.setEffect(CONDICIONS::ENEMY_DEAD,true);
  act.applyEffects(ws);

  ASSERT_EQ(ws,finalws);
}





