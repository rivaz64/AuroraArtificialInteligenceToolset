#include "auPlansGraph.h"
#include "auAction.h"
#include "auAStarNode.h"

namespace auToolSeetSDK{

void 
PlansGraph::buildGraph(Vector<Action>& actions)
{
  m_actions = actions;
  auto numOfActions = actions.size();

  m_graph.resize(numOfActions);
  for(auto& row : m_graph){
    row.resize(numOfActions);
  }

  for(uint32 precondicionNum = 0; precondicionNum<numOfActions; ++precondicionNum){
    for(uint32 effectNum = 0; effectNum<numOfActions; ++effectNum){
      if(precondicionNum == effectNum) continue;

      auto& precondicion = actions[precondicionNum].getPrecondicions();
      auto& effects = actions[effectNum].getEffects();

      if(precondicion.getNumOfDiferences(effects) == 0){
        m_graph[precondicionNum][effectNum] = true;
      }
    }
  }
}

Vector<uint32>
PlansGraph::getAdjacentNodes(uint32 nodeId)
{
  auto numOfActions = m_actions.size();
  Vector<uint32> adjacents;
  
  for(uint32 i = 0; i<numOfActions; ++i){
    if(m_graph[i][nodeId]){
      adjacents.push_back(i);
    }
  }

  return adjacents;
}

float 
PlansGraph::getCost(WPtr<SearchNode> wNode1, WPtr<SearchNode> wNode2)
{
  //if(!wNode2.expired()){
  //  auto node = wNode2.lock();
  //  return m_actions[node->id].getCost();
  //}
  //return 0;
  
}

float
PlansGraph::getHeuristicDistance(WPtr<SearchNode> wNode)
{
  //if(wNode.expired()){
  //  return 0.0f;
  //}
  //auto node = wNode.lock();
  //auto action = m_actions[node->id];
}

}

