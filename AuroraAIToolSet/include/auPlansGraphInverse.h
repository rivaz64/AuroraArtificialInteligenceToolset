/**
 * @file auPlansGraphInverse.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once
#include "auPlansGraph.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT PlansGraphInverse :
    public PlansGraph
{
 public: 

  PlansGraphInverse() = default;

  PlansGraphInverse(Vector<SPtr<Action>>&& actions) :
    PlansGraph(move(actions)) {}

  PlansGraphInverse(const Vector<SPtr<Action>>& actions) :
    PlansGraph(actions) {}

  Vector<SPtr<SearchNode>>
  getAdjacentNodes(WPtr<SearchNode> node) override;

  bool
  isAtGoal(uint32 nodeId, uint32 goal) override;

  SPtr<Plan>
  getPlan(const Vector<WPtr<SearchNode>>& path) override;
};

}


