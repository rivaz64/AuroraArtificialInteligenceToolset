#include "auSearchGraph.h"

namespace auToolSeetSDK
{

bool 
SearchGraph::isAtGoal(uint32 nodeId, uint32 goal)
{
  return nodeId == goal;
}

}

