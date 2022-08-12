#include "auPlansGraphInverse.h"
#include "auAction.h"
#include "auPlan.h"
#include "auPathFinder.h"

namespace auToolSeetSDK
{

Vector<SPtr<SearchNode>> 
PlansGraphInverse::getAdjacentNodes(WPtr<SearchNode> wNode)
{
  auto node = wNode.lock();
  WorldState ws(node->id);
  auto numOfActions = m_actions.size();
  Vector<SPtr<SearchNode>> adjacents;

  for(uint32 i = 0; i<numOfActions; ++i){
    if(m_actions[i]->isCompleted(ws)){
      auto newWS = ws;
      m_actions[i]->undo(newWS);
      auto newNode = makeSPtr<SearchNode>();
      newNode->id = newWS.getId();
      newNode->data["action"] = i;
      adjacents.push_back(newNode);
    }
  }

  return adjacents;
}

bool 
PlansGraphInverse::isAtGoal(uint32 nodeId, uint32 goal)
{
  WorldState ws(nodeId);
  WorldState goalWS(goal);
  return ws.satisfies(goalWS);
}

SPtr<Plan>
PlansGraphInverse::getPlan(const Vector<WPtr<SearchNode>>& path)
{
  auto plan = makeSPtr<Plan>();
  auto size = path.size();

  for(uint32 i = 0; i<size; ++i){
    uint32 actionId = path[i].lock()->data["action"];
    plan->addAction(m_actions[actionId]);
  }
  
  return plan;
}

}