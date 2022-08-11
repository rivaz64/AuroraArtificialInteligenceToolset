#include "auGoapPlanner.h"
#include "auPlansGraph.h"
#include "auBreadthFirstSearch.h"
#include "auPlan.h"

namespace auToolSeetSDK
{

void 
GoapPlanner::setGoal(const WorldState& ws)
{
  m_goal = ws;
}

void
GoapPlanner::update(WorldState& ws)
{
  if(!m_plan){
    if(m_graph.expired()) return;
    auto graph = m_graph.lock();
    BreadthFirstSearch searcher;
    searcher.setGraph(m_graph);
    searcher.setSourceId(ws.getId());
    searcher.setGoalId(m_goal.getId());
    auto result = searcher.run();
    auto path = searcher.getPath();
    m_plan = graph->getPlan(path);
    m_plan->execute();
  }
  else{
    if(m_plan->update(ws) == PLAN_STATE::kFailed){
      m_plan.reset();
    }
  }

}

}

