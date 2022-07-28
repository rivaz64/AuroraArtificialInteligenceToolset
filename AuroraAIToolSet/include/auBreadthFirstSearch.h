/**
 * @file auBreadthFirstSearch.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPathFinder.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT BreadthFirstSearch :
  public PathFinder
{
 protected:
  
  void
  addNodeToOpenList(WPtr<SearchNode> node) override;
};

}


