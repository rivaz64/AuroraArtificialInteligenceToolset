/**
 * @file auAstar.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auPathFinder.h"

namespace auToolSeetSDK
{

/**
 * @brief class for doing aStar searches
*/
class AU_UTILITY_EXPORT AStar :
  public PathFinder
{
 public:

 protected:

  void
  addDataToNode(WPtr<SearchNode> node, WPtr<SearchNode> parent) override;

  void
  addNodeToOpenList(WPtr<SearchNode> node) override;

  bool
  isBetterPath(WPtr<SearchNode> node, WPtr<SearchNode> newParent) override;  
};

}


