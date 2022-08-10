#include "auDijistra.h"

namespace auToolSeetSDK
{

void 
Dijistra::addDataToNode(WPtr<SearchNode> wNode, WPtr<SearchNode> wParent)
{
  if(wNode.expired() || wParent.expired()) return;
  auto node = cast<DijistraNode>(wNode.lock());
  auto parent = cast<DijistraNode>(wParent.lock());
  auto graph = m_graph.lock();
  //node->cost = parent->cost + m_graph->
}

}

