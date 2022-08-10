/**
 * @file auPlansGraph.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auSearchGraph.h"
#include "auAction.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT PlansGraph :
  public SearchGraph
{
 public:
  
  PlansGraph() = default;

  PlansGraph(Vector<SPtr<Action>>&& actions) :
    m_actions(move(actions)) {}

  PlansGraph(const Vector<SPtr<Action>>& actions) :
    m_actions(actions) {}

  Vector<uint32>
  getAdjacentNodes(uint32 nodeId) override;

  FORCEINLINE void
  addAction(SPtr<Action> action)
  {
    m_actions.push_back(action);
  }

  /**
   * @brief gets the path from a path obtained from a search
   * @param path the path of id of nodes
   * @return a plan of actions
  */
  SPtr<Plan>
  getPlan(const Vector<uint32>& path);

  float
  getCost(WPtr<SearchNode> node1, WPtr<SearchNode> node2) override;

  float
  getHeuristicDistance(WPtr<SearchNode> node) override;

  bool
  isAtGoal(uint32 nodeId, uint32 goal) override;

 private:

  /**
   * @brief tha actions of this graph toconsider
  */
  Vector<SPtr<Action>> m_actions;
};

}



