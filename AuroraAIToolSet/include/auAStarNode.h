/**
 * @file auAStarNode.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK{

/**
 * @brief node used for building the graph used for AStar search;
*/
struct AStarNode
{
 public:
 
  AStarNode(float _toGoal, float _heuristic) :
   toGoal(_toGoal), heuristic(_heuristic) {}

  FORCEINLINE float
  getFitness(){
    return toGoal+heuristic;
  }

  /**
   * @brief the distance from this node to the goal
  */
  float toGoal;

  /**
   * @brief the cost from the source to this node
  */
  float heuristic;
};

}


