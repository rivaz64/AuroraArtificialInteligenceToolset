#include "auPlan.h"
#include "auAction.h"

namespace auToolSeetSDK
{

void 
Plan::addAction(WPtr<Action> action)
{
  m_actions.push_back(action);
}

void
Plan::execute()
{
  m_actualAction = 0;
  if(m_actions.size()>0){
    auto& wAction = m_actions[0];
    if(wAction.expired()) return;
    auto action = wAction.lock();
    action->execute();
  }
}

PLAN_STATE::E 
Plan::update(WorldState& ws)
{
  auto wAction = m_actions[0];
  if(wAction.expired()) return PLAN_STATE::kFailed;
  auto action = wAction.lock();

  if(!action->validatePrecondicions(ws)){
    action->deactivate();
    return PLAN_STATE::kFailed;
  }

  if(action->completed()){
    action->applyEffects(ws);
    ++m_actualAction;
    if(m_actualAction == m_actions.size()){
      return PLAN_STATE::kCompleted;
    }
  }

  wAction = m_actions[0];
  if(wAction.expired()) return PLAN_STATE::kFailed;
  action = wAction.lock();


  if(action->validatePrecondicions(ws)){
    action->execute();
    return PLAN_STATE::kExecuting;
  }

  return PLAN_STATE::kFailed;
}

}

