/**
 * @file auGoapPlanner.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auWorldState.h"

namespace auToolSeetSDK
{

class GoapPlanner
{
 public: 

  GoapPlanner(WPtr<PlansGraph> plans) :
    m_graph(plans) {}

  void
  setGoal(const WorldState& ws);

  void
  update(WorldState& ws);

 protected:

  /**
   * @brief the graph for all the actions this planner can execute
  */
  WPtr<PlansGraph> m_graph;

  /**
   * @brief the plan actualy executing
  */
  SPtr<Plan> m_plan;

  /**
   * @brief the goal this planner is trying to achive
  */
  WorldState m_goal;
};

}


