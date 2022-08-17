#include "auSearchGraph.h"
#include "auPathFinder.h"

namespace auToolSeetSDK
{

bool 
SearchGraph::isAtGoal(WPtr<SearchNode> node, uint32 goal)
{
  return node.lock()->id == goal;
}

}

