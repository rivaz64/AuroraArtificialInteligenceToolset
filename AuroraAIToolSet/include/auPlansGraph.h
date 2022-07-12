/**
 * @file auPlansGraph.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auAStarGraph.h"

namespace auToolSeetSDK{

class PlansGraph :
  public AStarGraph
{
 public:
  
  /**
   * @brief buils the graph with all the posible paths of action of a certain group of actions
   * @param actions 
  */
  void
  buildGraph(Vector<Action>& actions);

  Vector<uint32>
  getAdjacentNodes(uint32 nodeId) override;

 private:

  /**
   * @brief tha actions of this graph toconsider
  */
  Vector<Action> m_actions;

  /**
   * @brief the matrix of the graph
  */
  Vector<Vector<bool>> m_graph;
};

}



