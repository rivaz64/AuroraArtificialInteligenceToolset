/**
 * @file auAstar.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auPathFinder.h"

namespace auToolSeetSDK{
/**
 * @brief node used for building the graph used for AStar search;
*/
struct AStarNode :
  public SearchNode
{
 public:
 
  AStarNode() = default;
  //AStarNode(float _toGoal, float _heuristic) :
  // toGoal(_toGoal), heuristic(_heuristic) {}

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


/**
 * @brief class for doing aStar searches
*/
class AStar :
  public PathFinder
{
 public:

 protected:

  void
  addDataToNode(WPtr<SearchNode> node) override;

  bool
  isBetterPath(WPtr<AStarNode> node, WPtr<AStarNode> newParent);

  void
  addNodeToOpenList(WPtr<SearchNode> node) override;

  void
  analizeNode(WPtr<SearchNode> node, WPtr<SearchNode> newParent) override;

  /**
   * @brief the paths that have been searched
  */
  //Vector<uint32> m_closedList;

  

  
};

}


