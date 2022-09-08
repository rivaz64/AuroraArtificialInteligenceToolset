#include "auPlan.h"
#include "auAction.h"

namespace auToolSeetSDK
{

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
Plan::update(const WorldState& ws)
{
  if(m_actions.size()==0) return PLAN_STATE::kFailed;
  if(m_actions.size()==m_actualAction) return PLAN_STATE::kCompleted;
  auto wAction = m_actions[m_actualAction];
  if(wAction.expired()) return PLAN_STATE::kFailed;
  auto action = wAction.lock();

  if(action->isCompleted(ws)){
    action->deactivate();
    ++m_actualAction;
    if(m_actualAction == m_actions.size()){
      return PLAN_STATE::kCompleted;
    }
    wAction = m_actions[m_actualAction];
    if(wAction.expired()) return PLAN_STATE::kFailed;
    action = wAction.lock();

    if(action->validatePrecondicions(ws)){
      action->execute();
      return PLAN_STATE::kExecuting;
    }
    return PLAN_STATE::kFailed;
  }
  else if(!action->validatePrecondicions(ws)){
    action->deactivate();
    return PLAN_STATE::kFailed;
  }
  else
  {
    action->update();
    return PLAN_STATE::kExecuting;
  }
}

}

