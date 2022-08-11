/**
 * @file auDijistra.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auPathFinder.h"

namespace auToolSeetSDK
{

/**
 * @brief node used for dijistra searches
*/
//struct DijistraNode :
//  public SearchNode
//{
//  /**
//   * @brief the cost 
//  */
//  float cost;
//};

/**
 * @brief class for doing Dijistra searches
*/
class AU_UTILITY_EXPORT Dijistra :
  public PathFinder
{
 public:

  void
  addDataToNode(WPtr<SearchNode> node, WPtr<SearchNode> parent) override;

  void
  addNodeToOpenList(WPtr<SearchNode> node);

  virtual bool
  isBetterPath(WPtr<SearchNode> node, WPtr<SearchNode> newParent);
};

}

