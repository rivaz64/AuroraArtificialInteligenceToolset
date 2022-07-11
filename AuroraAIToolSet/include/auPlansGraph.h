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
 
  void
  buildGraph(const Vector<Action>& actions);

 private:
};

}



