/**
 * @file auAStarGraph.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK{

/**
 * @brief a graph that a seach can be done in
*/
class SearchGraph
{
 public:

  /**
   * @brief gets the nodes adjacent to one
   * @param nodeId the id of node to which they are adjacent
   * @return the ids of the adjacent nodes
  */
  virtual Vector<uint32>
  getAdjacentNodes(uint32 nodeId)
  {
    return {};
  }

  /**
   * @brief gets the cost of going from node1 to node2
   * @param nodeId1 the distance of the first node
   * @param nodeId2 the distance of the second node
   * @return the cost
  */
  virtual float
  getCost(WPtr<SearchNode> node1, WPtr<SearchNode> node2);

  /**
   * @brief gets the distance between 2 nodes
   * @param nodeId1 the distance of the first node
   * @param nodeId2 the distance of the second node
   * @return the distance
  */
  virtual float
  getHeuristicDistance(WPtr<SearchNode> nodeId);

 private:

};

}



