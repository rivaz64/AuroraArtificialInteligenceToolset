#include "pch.h"

#include "auWorldState.h"
#include "auAction.h"
#include "auPlansGraph.h"
#include "Flags.h"
#include "Attack.h"

using auToolSeetSDK::WorldState;
using auToolSeetSDK::Action;
using auToolSeetSDK::PlansGraph;
using auToolSeetSDK::Vector;
using auToolSeetSDK::Attack;

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}

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

  WorldState::defineCondicion(HAS_WEAPON_RANGED);
  WorldState::defineCondicion(HAS_WEAPON_MELEE);
  WorldState::defineCondicion(HAS_WEAPON_THROWN);
  WorldState::defineCondicion(WEAPON_LOADED);
  WorldState::defineCondicion(ENEMY_DEAD);
  WorldState::defineCondicion(AT_TARGET_LOCATION);
  WorldState::defineCondicion(DISTURBANCE_EXISTS);

  Attack attack(HAS_WEAPON_RANGED,WEAPON_LOADED);
  attack.addPrecondicion(WEAPON_LOADED,true);

  Attack attackMelee(HAS_WEAPON_MELEE,ENEMY_IN_MELEE_RANGE);

  Attack attackThrow(HAS_WEAPON_THROWN,ENEMY_IN_THROWN_RANGE);

  Action investigateDisturbance;
  investigateDisturbance.setPrecondicions(WorldState({{HAS_WEAPON,true},
                                                     {AT_TARGET_LOCATION,true}}));
  investigateDisturbance.setEffects(WorldState({{DISTURBANCE_EXISTS,false}}));

  Action lookDisturbance;
  investigateDisturbance.setPrecondicions(WorldState({{HAS_WEAPON,true}}));
  investigateDisturbance.setEffects(WorldState({{DISTURBANCE_EXISTS,false}}));

  Action surveyArea;
  surveyArea.setPrecondicions(WorldState({{HAS_WEAPON,true}}));
  surveyArea.setEffects(WorldState({{SURVEYED_AREA,true}}));

  Action opedDoor;
  investigateDisturbance.setEffects(WorldState({{DOOR_CLOSED,false}}));

  //graph.buildGraph();
}