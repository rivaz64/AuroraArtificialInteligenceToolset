#include "pch.h"

#include "auWorldState.h"
#include "auAction.h"
#include "auPlansGraph.h"
#include "auPlansGraphInverse.h"
#include "auBreadthFirstSearch.h"
#include "auPlan.h"
#include "auDijistra.h"

using auToolSeetSDK::WorldState;
using auToolSeetSDK::Action;
using auToolSeetSDK::PlansGraph;
using auToolSeetSDK::PlansGraphInverse;
using auToolSeetSDK::Vector;
using auToolSeetSDK::BreadthFirstSearch;
using auToolSeetSDK::makeSPtr;
using auToolSeetSDK::SPtr;
using auToolSeetSDK::SearchNode;
using auToolSeetSDK::Dijistra;

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
KNIFE_PREPARED,
WEAPON_IN_HAND,
ME_DEAD
};
}

Vector<SPtr<Action>> actions;
SPtr<Action> patrol = makeSPtr<Action>("patrol",250);
SPtr<Action> aproach = makeSPtr<Action>("aproach",2);
SPtr<Action> aproachClose = makeSPtr<Action>("aproachClose",4);
SPtr<Action> loadGun = makeSPtr<Action>("loadGun",2);
SPtr<Action> prepareGun = makeSPtr<Action>("prepareGun",1);
SPtr<Action> putAwayGun = makeSPtr<Action>("putAwayGun",1);
SPtr<Action> prepareKnife = makeSPtr<Action>("prepareKnife",1);
SPtr<Action> putAwayKnife = makeSPtr<Action>("putAwayKnife",1);
SPtr<Action> shoot = makeSPtr<Action>("shoot",3);
SPtr<Action> stab = makeSPtr<Action>("stab",3);
SPtr<Action> suicide = makeSPtr<Action>("suicide",30);

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
  WorldState::defineCondicion(CONDICIONS::KNIFE_PREPARED);
  WorldState::defineCondicion(CONDICIONS::WEAPON_IN_HAND);
  WorldState::defineCondicion(CONDICIONS::ME_DEAD);
}

void
createActions()
{
  
  patrol->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  patrol->setPrecondicion(CONDICIONS::WEAPON_IN_HAND,true);
  patrol->setEffect(CONDICIONS::ENEMY_IN_SIGHT,true);
  actions.push_back(patrol);
  
  aproach->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  aproach->setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  aproach->setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, false);
  aproach->setPrecondicion(CONDICIONS::GUN_LOADED, true);
  aproach->setEffect(CONDICIONS::ENEMY_IN_RANGE, true);
  actions.push_back(aproach);

  
  aproachClose->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  aproachClose->setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  aproachClose->setPrecondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE, false);
  aproachClose->setEffect(CONDICIONS::ENEMY_IN_CLOSE_RANGE, true);
  actions.push_back(aproachClose);

  
  loadGun->setPrecondicion(CONDICIONS::HAS_BULLETS, true);
  loadGun->setPrecondicion(CONDICIONS::GUN_LOADED, false);
  loadGun->setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  loadGun->setEffect(CONDICIONS::GUN_LOADED, true);
  loadGun->setEffect(CONDICIONS::HAS_BULLETS, false);
  actions.push_back(loadGun);

  
  prepareGun->setPrecondicion(CONDICIONS::HAS_GUN, true);
  prepareGun->setPrecondicion(CONDICIONS::WEAPON_IN_HAND, false);
  prepareGun->setPrecondicion(CONDICIONS::GUN_PREPARED, false);
  prepareGun->setEffect(CONDICIONS::WEAPON_IN_HAND, true);
  prepareGun->setEffect(CONDICIONS::GUN_PREPARED, true);
  actions.push_back(prepareGun);

  
  putAwayGun->setPrecondicion(CONDICIONS::WEAPON_IN_HAND, true);
  putAwayGun->setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  putAwayGun->setEffect(CONDICIONS::GUN_PREPARED, false);
  putAwayGun->setEffect(CONDICIONS::WEAPON_IN_HAND, false);
  actions.push_back(putAwayGun);

  
  prepareKnife->setPrecondicion(CONDICIONS::HAS_KNIFE, true);
  prepareKnife->setPrecondicion(CONDICIONS::WEAPON_IN_HAND, false);
  prepareKnife->setPrecondicion(CONDICIONS::KNIFE_PREPARED, false);
  prepareKnife->setEffect(CONDICIONS::KNIFE_PREPARED, true);
  prepareKnife->setEffect(CONDICIONS::WEAPON_IN_HAND, true);
  actions.push_back(prepareKnife);

  
  putAwayKnife->setPrecondicion(CONDICIONS::KNIFE_PREPARED, true);
  putAwayKnife->setPrecondicion(CONDICIONS::WEAPON_IN_HAND, true);
  putAwayKnife->setEffect(CONDICIONS::WEAPON_IN_HAND, false);
  putAwayKnife->setEffect(CONDICIONS::KNIFE_PREPARED, false);
  actions.push_back(putAwayKnife);

  
  shoot->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  shoot->setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  shoot->setPrecondicion(CONDICIONS::GUN_PREPARED, true);
  shoot->setPrecondicion(CONDICIONS::GUN_LOADED, true);
  shoot->setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, true);
  shoot->setEffect(CONDICIONS::ENEMY_DEAD, true);
  actions.push_back(shoot);

  
  stab->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  stab->setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  stab->setPrecondicion(CONDICIONS::KNIFE_PREPARED, true);
  stab->setPrecondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE, true);
  stab->setEffect(CONDICIONS::ENEMY_DEAD, true);
  actions.push_back(stab);

  
  suicide->setPrecondicion(CONDICIONS::ENEMY_IN_SIGHT, true);
  suicide->setPrecondicion(CONDICIONS::ENEMY_DEAD, false);
  suicide->setPrecondicion(CONDICIONS::ENEMY_IN_RANGE, true);
  suicide->setEffect(CONDICIONS::ENEMY_DEAD, true);
  suicide->setEffect(CONDICIONS::ME_DEAD, true);
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
    goal.setCondicion(CONDICIONS::ME_DEAD,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(CONDICIONS::HAS_GUN,false);
    ws.setCondicion(CONDICIONS::ME_DEAD,false);
    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, nothingMatters) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::ME_DEAD,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMatters) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::ME_DEAD,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);

    ASSERT_TRUE(ws.satisfies(goal));
}

TEST_F(WorldStateTest, someMattersDifferentValues) {
    WorldState goal;
    goal.setCondicion(CONDICIONS::HAS_BULLETS,false);
    goal.setCondicion(CONDICIONS::HAS_GUN,false);
    goal.setCondicion(CONDICIONS::ME_DEAD,false);

    ws.setCondicion(CONDICIONS::HAS_BULLETS,false);
    ws.setCondicion(CONDICIONS::HAS_GUN,true);

    ASSERT_EQ(ws.getNumOfUnsatisfiedCondicion(goal),1);
}

TEST_F(ActionTest, canDoAction) {
  act.setPrecondicion(CONDICIONS::HAS_GUN,true);
  act.setPrecondicion(CONDICIONS::ME_DEAD,false);

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::ME_DEAD,false);

  ASSERT_TRUE(act.validatePrecondicions(ws));
}

TEST_F(ActionTest, cantDoAction) {
  act.setPrecondicion(CONDICIONS::HAS_GUN,true);
  act.setPrecondicion(CONDICIONS::ME_DEAD,true);

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::ME_DEAD,false);

  ASSERT_FALSE(act.validatePrecondicions(ws));
}

TEST_F(ActionTest, realTest) {
  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  ASSERT_TRUE(prepareGun->validatePrecondicions(currentWS));
}

TEST_F(ActionTest, realTestIncorrect) {
  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  ASSERT_FALSE(putAwayGun->validatePrecondicions(currentWS));
}

TEST_F(ActionTest, noEffects) {

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::ME_DEAD,false);

  auto prevWS = ws;
  act.applyEffects(ws);

  ASSERT_EQ(prevWS,ws);
}

TEST_F(ActionTest, wsAfected) {

  WorldState ws;
  ws.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  ws.setCondicion(CONDICIONS::HAS_GUN,true);
  ws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  ws.setCondicion(CONDICIONS::ME_DEAD,false);

  WorldState finalws;
  finalws.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  finalws.setCondicion(CONDICIONS::HAS_GUN,true);
  finalws.setCondicion(CONDICIONS::HAS_BULLETS,true);
  finalws.setCondicion(CONDICIONS::ME_DEAD,false);

  act.setPrecondicion(CONDICIONS::ENEMY_DEAD,false);
  act.setEffect(CONDICIONS::ENEMY_DEAD,true);
  act.applyEffects(ws);

  ASSERT_EQ(ws,finalws);
}

TEST(IDtest,idTest){
  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  WorldState newWS(currentWS.getId());
  bool eq = newWS==currentWS;
  ASSERT_TRUE(newWS==currentWS);
}

TEST(GraphTest, adjacentNodesBasic){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);


  auto plans = makeSPtr<PlansGraph>(actions);
  auto node = makeSPtr<SearchNode>();
  node->id = currentWS.getId();
  auto adjacents = plans->getAdjacentNodes(node);
  ASSERT_FALSE(adjacents.size()==0);
}

TEST(GraphTest, adjacentNodesAdvanced){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);


  auto plans = makeSPtr<PlansGraph>(actions);
  auto node = makeSPtr<SearchNode>();
  node->id = currentWS.getId();
  auto adjacents = plans->getAdjacentNodes(node);
  ASSERT_TRUE(adjacents.size()==2);
}

TEST(GraphTest, effects){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  

  auto plans = makeSPtr<PlansGraph>(actions);
  prepareGun->applyEffects(currentWS);
  ASSERT_TRUE(patrol->validatePrecondicions(currentWS));
}

TEST(GraphTest, inverse){
  WorldState goalWS;
  goalWS.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  goalWS.setCondicion(CONDICIONS::ME_DEAD,false);
  goalWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,true);

  auto plans = makeSPtr<PlansGraphInverse>(actions);
  auto node = makeSPtr<SearchNode>();
  node->id = goalWS.getId();
  auto adjacents = plans->getAdjacentNodes(node);
  ASSERT_TRUE(adjacents.size()==2);
}

TEST(PlanTest, basic){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  WorldState goalWS;
  goalWS.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  goalWS.setCondicion(CONDICIONS::ME_DEAD,false);
  goalWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,true);

  auto plans = makeSPtr<PlansGraph>(actions);

  //auto adjacents = plans->getAdjacentNodes(currentWS.getId());
  //ASSERT_FALSE(adjacents.size()==0);
   
  
  BreadthFirstSearch searcher;
  searcher.setGraph(plans);
  searcher.setSourceId(currentWS.getId());
  searcher.setGoalId(goalWS.getId());
  auto result = searcher.run();
  auto path = searcher.getPath();
  
  auto plan = plans->getPlan(path);
  
  ASSERT_TRUE(plan->m_actions.size()!=0);

}

TEST(PlanTest, cost){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  WorldState goalWS;
  goalWS.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  goalWS.setCondicion(CONDICIONS::ME_DEAD,false);
  goalWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,true);

  auto plans = makeSPtr<PlansGraph>(actions);

  Dijistra searcher;
  searcher.setGraph(plans);
  searcher.setSourceId(currentWS.getId());
  searcher.setGoalId(goalWS.getId());
  auto result = searcher.run();
  auto path = searcher.getPath();
  
  auto plan = plans->getPlan(path);
  
  ASSERT_TRUE(plan->m_actions.size()!=0);

}

TEST(PlanTest, inverse){

  WorldState currentWS;
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_SIGHT,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_DEAD,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_RANGE,false);
  currentWS.setCondicion(CONDICIONS::ENEMY_IN_CLOSE_RANGE,false);
  currentWS.setCondicion(CONDICIONS::HAS_KNIFE,true);
  currentWS.setCondicion(CONDICIONS::HAS_GUN,true);
  currentWS.setCondicion(CONDICIONS::GUN_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::GUN_LOADED,false);
  currentWS.setCondicion(CONDICIONS::HAS_BULLETS,true);
  currentWS.setCondicion(CONDICIONS::KNIFE_PREPARED,false);
  currentWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,false);
  currentWS.setCondicion(CONDICIONS::ME_DEAD,false);

  WorldState goalWS;
  goalWS.setCondicion(CONDICIONS::ENEMY_DEAD,true);
  goalWS.setCondicion(CONDICIONS::ME_DEAD,false);
  goalWS.setCondicion(CONDICIONS::WEAPON_IN_HAND,true);

  auto plans = makeSPtr<PlansGraphInverse>(actions);

  Dijistra searcher;
  searcher.setGraph(plans);
  searcher.setSourceId(goalWS.getId());
  searcher.setGoalId(currentWS.getId());
  auto result = searcher.run();
  auto path = searcher.getPath();
  
  auto plan = plans->getPlan(path);

  for(auto& action : plan->m_actions){
    auToolSeetSDK::print(action.lock()->getName());
  }

  ASSERT_TRUE(plan->m_actions.size()!=0);

}





