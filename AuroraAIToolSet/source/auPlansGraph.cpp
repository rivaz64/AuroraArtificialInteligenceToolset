#include "auPlansGraph.h"
#include "auAction.h"

namespace auToolSeetSDK{

//void 
//PlansGraph::buildGraph(Vector<Action>& actions)
//{
//  m_actions = actions;
//  auto numOfActions = actions.size();
//
//  m_graph.resize(numOfActions);
//  for(auto& row : m_graph){
//    row.resize(numOfActions);
//  }
//
//  for(uint32 precondicionNum = 0; precondicionNum<numOfActions; ++precondicionNum){
//    for(uint32 effectNum = 0; effectNum<numOfActions; ++effectNum){
//      if(precondicionNum == effectNum) continue;
//
//      auto& precondicion = actions[precondicionNum].getPrecondicions();
//      auto& effects = actions[effectNum].getEffects();
//
//      if(precondicion.getNumOfDiferences(effects) == 0){
//        m_graph[precondicionNum][effectNum] = true;
//      }
//    }
//  }
//}

Vector<uint32>
PlansGraph::getAdjacentNodes(uint32 nodeId)
{
  WorldState ws(nodeId);
  auto numOfActions = m_actions.size();
  Vector<uint32> adjacents;
  for(uint32 i = 0; i<numOfActions; ++i){
    
    if(m_actions[i].validatePrecondicions(ws)){
      auto newWS = ws;
      m_actions[i].applyEffects(newWS);
      uint32 id = newWS.getId();
      auto nodeId = id | (i<<28);
      adjacents.push_back(nodeId);
    }
  }

  return adjacents;
}

Vector<Action> 
PlansGraph::getPlan(const Vector<uint32>& path)
{
  Vector<Action> plan;
  auto size = path.size();
  plan.resize(size);

  for(uint32 i = 0; i<size; ++i){
    uint32 actionId = path[i]>>28;
    plan[i] = m_actions[actionId];
  }
  return plan;
}

float 
PlansGraph::getCost(WPtr<SearchNode> wNode1, WPtr<SearchNode> wNode2)
{
  //if(!wNode2.expired()){
  //  auto node = wNode2.lock();
  //  return m_actions[node->id].getCost();
  //}
  return 0;
  
}

float
PlansGraph::getHeuristicDistance(WPtr<SearchNode> wNode)
{
  //if(wNode.expired()){
    return 0.0f;
  //}
  //auto node = wNode.lock();
  //auto action = m_actions[node->id];
}

bool 
PlansGraph::isAtGoal(uint32 nodeId, uint32 goal)
{
  WorldState ws(nodeId);
  WorldState goalWS(goal);
  String action = m_actions[nodeId>>28].getName();
  return goalWS.satisfies(ws);
}

}

