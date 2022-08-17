#include "auAStar.h"
#include "auSearchGraph.h"

namespace auToolSeetSDK
{

void
AStar::addDataToNode(WPtr<SearchNode> wNode, WPtr<SearchNode> wParent)
{
  if(wNode.expired() || wParent.expired()) return;
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  node->data["cost"] = parent->data["cost"] + graph->getCost(wParent,node);
  node->data["distance"] = graph->getHeuristicDistance(wParent,node);
  node->data["f"] = node->data["cost"] + node->data["distance"]; 
}

void 
AStar::addNodeToOpenList(WPtr<SearchNode> wNode)
{
  auto newNode = wNode.lock();
  for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
    auto node = it->lock();
    if(node->data["f"] > newNode->data["f"]){
      m_openList.insert(it,newNode);
      return;
    }
  }
  m_openList.push_back(newNode);
}

bool 
AStar::isBetterPath(WPtr<SearchNode> wNode, WPtr<SearchNode> wParent)
{
  if(wNode.expired() || wParent.expired()) return false;
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  return node->data["f"] > node->data["distance"]+parent->data["cost"] + graph->getCost(wParent,node);
}

}
