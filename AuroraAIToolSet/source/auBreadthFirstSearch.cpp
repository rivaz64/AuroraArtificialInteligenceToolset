#include "auBreadthFirstSearch.h"

namespace auToolSeetSDK{

void 
BreadthFirstSearch::addNodeToOpenList(WPtr<SearchNode> node)
{
  m_openList.push_back(node);
}

}

