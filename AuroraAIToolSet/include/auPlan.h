/**
 * @file auPlan.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK
{

namespace PLAN_STATE
{
enum E{
kFailed,
kCompleted,
kExecuting
};
}

class AU_UTILITY_EXPORT Plan
{
 public:

  /**
   * @brief adds an action to the plan
   * @param action 
  */
  FORCEINLINE void
  addAction(WPtr<Action> action)
  {
    m_actions.push_back(action);
  }

  /**
   * @brief starts executing this plan
  */
  void
  execute();

  /**
   * @brief to keep executing the plan
   * @param ws the current world state of the pawn
  */
  PLAN_STATE::E
  update(const WorldState& ws);

 public:

  /**
   * @brief the plans to execute in this order
  */
  Vector<WPtr<Action>> m_actions;

  /**
   * @brief the action is executing now
  */
  uint32 m_actualAction;

  friend class PlansGraph;
};


}


