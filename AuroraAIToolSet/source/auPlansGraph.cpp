#include "auPlansGraph.h"
#include "auAction.h"
#include "auPlan.h"
#include "auPathFinder.h"

namespace auToolSeetSDK
{

Vector<SPtr<SearchNode>>
PlansGraph::getAdjacentNodes(WPtr<SearchNode> wNode)
{
  auto node = wNode.lock();
  WorldState ws(node->id);
  auto numOfActions = m_actions.size();
  Vector<SPtr<SearchNode>> adjacents;

  for(uint32 i = 0; i<numOfActions; ++i){
    if(m_actions[i]->validatePrecondicions(ws)){
      auto newWS = ws;
      m_actions[i]->applyEffects(newWS);
      auto newNode = makeSPtr<SearchNode>();
      newNode->id = newWS.getId();
      newNode->data["action"] = i;
      adjacents.push_back(newNode);
    }
  }

  return adjacents;
}

SPtr<Plan>
PlansGraph::getPlan(const Vector<WPtr<SearchNode>>& path)
{
  auto plan = makeSPtr<Plan>();
  auto size = path.size();

  for(uint32 i = 0; i<size; ++i){
    uint32 actionId = path[i].lock()->data["action"];
    plan->addAction(m_actions[actionId]);
  }
  plan->invert();
  
  return plan;
}

float 
PlansGraph::getCost(WPtr<SearchNode> wNode1, WPtr<SearchNode> wNode2)
{
  if(!wNode2.expired()){
    auto node = wNode2.lock();
    return m_actions[node->data["action"]]->getCost();
  }
  return 0;
  
}

float
PlansGraph::getHeuristicDistance(WPtr<SearchNode> node, WPtr<SearchNode> goal)
{
  WorldState ws(node.lock()->id);
  WorldState goalWS(goal.lock()->id);
  return goalWS.getNumOfUnsatisfiedCondicion(ws);
}

bool 
PlansGraph::isAtGoal(WPtr<SearchNode> node, uint32 goal)
{
  WorldState ws(node.lock()->id);
  WorldState goalWS(goal);
  return goalWS.satisfies(ws);
}

}

