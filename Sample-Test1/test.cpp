#include "pch.h"

#include "auWorldState.h"
#include "auAction.h"
#include "auPlansGraph.h"

using auToolSeetSDK::WorldState;
using auToolSeetSDK::Action;
using auToolSeetSDK::PlansGraph;
using auToolSeetSDK::Vector;

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}

enum CONDICIONS{
  HAS_WEAPON,
  HAS_BULLETS,
  PLAYER_DEAD
};

TEST(FlagDefines, FlagPositions) {
  
}

//TEST(FlagComparations, SameFlagsSameMask) {
//  WorldState ws1, ws2;
//
//  ws1.addCondicion(HAS_WEAPON);
//  ws1.addCondicion(PLAYER_IN_RANGE);
//  ws1.setCondicion(HAS_WEAPON,true);
//  ws1.setCondicion(PLAYER_IN_RANGE,true);
//
//  ws2.addCondicion(HAS_WEAPON);
//  ws2.addCondicion(PLAYER_IN_RANGE);
//  ws2.setCondicion(HAS_WEAPON,true);
//  ws2.setCondicion(PLAYER_IN_RANGE,true);
//
//  EXPECT_EQ(ws1.getNumOfDiferences(ws2),0);
//}
//
//
//TEST(FlagComparations,  DiferentFlagsSameMask) {
//  WorldState ws1, ws2;
//
//  ws1.addCondicion(HAS_WEAPON);
//  ws1.addCondicion(PLAYER_IN_RANGE);
//  ws1.addCondicion(PLAYER_DEAD);
//  ws1.setCondicion(HAS_WEAPON,true);
//  ws1.setCondicion(PLAYER_IN_RANGE,true);
//  ws1.setCondicion(PLAYER_DEAD,true);
//
//  ws2.addCondicion(HAS_WEAPON);
//  ws2.addCondicion(PLAYER_IN_RANGE);
//  ws2.addCondicion(PLAYER_DEAD);
//  ws2.setCondicion(HAS_WEAPON,false);
//  ws2.setCondicion(PLAYER_IN_RANGE,true);
//  ws1.setCondicion(PLAYER_DEAD,false);
//
//  EXPECT_EQ(ws1.getNumOfDiferences(ws2),2);
//}
//
//TEST(FlagComparations, sameFlagsDiferentMask) {
//  WorldState ws1, ws2;
//
//  ws1.addCondicion(HAS_BULLETS);
//  ws1.addCondicion(PLAYER_IN_RANGE);
//  ws1.addCondicion(PLAYER_DEAD);
//  ws1.setCondicion(HAS_BULLETS,true);
//  ws1.setCondicion(PLAYER_IN_RANGE,true);
//  ws1.setCondicion(PLAYER_DEAD,true);
//
//  ws2.addCondicion(HAS_WEAPON);
//  ws2.addCondicion(PLAYER_IN_RANGE);
//  ws2.addCondicion(PLAYER_DEAD);
//  ws2.setCondicion(HAS_WEAPON,true);
//  ws2.setCondicion(PLAYER_IN_RANGE,true);
//  ws1.setCondicion(PLAYER_DEAD,true);
//
//  EXPECT_EQ(ws1.getNumOfDiferences(ws2),2);
//}
//
//
//TEST(FlagComparations, DiferentFlagsDiferentMask) {
//  WorldState ws1, ws2;
//
//  ws1.addCondicion(HAS_BULLETS);
//  ws1.addCondicion(PLAYER_IN_RANGE);
//  ws1.addCondicion(PLAYER_DEAD);
//  ws1.setCondicion(HAS_BULLETS,true);
//  ws1.setCondicion(PLAYER_IN_RANGE,true);
//  ws1.setCondicion(PLAYER_DEAD,true);
//
//  ws2.addCondicion(HAS_WEAPON);
//  ws2.addCondicion(PLAYER_IN_RANGE);
//  ws2.addCondicion(PLAYER_DEAD);
//  ws2.setCondicion(HAS_WEAPON,false);
//  ws2.setCondicion(PLAYER_IN_RANGE,false);
//  ws1.setCondicion(PLAYER_DEAD,false);
//
//  EXPECT_EQ(ws1.getNumOfDiferences(ws2),4);
//}

TEST(FlagComparations, DiferentFlagsDiferentMask) {

  WorldState::defineCondicion(HAS_WEAPON);
  WorldState::defineCondicion(HAS_BULLETS);
  WorldState::defineCondicion(PLAYER_DEAD);

  PlansGraph graph;
  Action attack;
  WorldState ws;
  attack.setPrecondicions();
  graph.buildGraph();
}