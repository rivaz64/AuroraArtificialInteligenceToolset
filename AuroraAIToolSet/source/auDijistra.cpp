#include "auDijistra.h"
#include "auSearchGraph.h"
namespace auToolSeetSDK
{

void 
Dijistra::addDataToNode(WPtr<SearchNode> wNode, WPtr<SearchNode> wParent)
{
  if(wNode.expired() || wParent.expired()) return;
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  node->data["cost"] = parent->data["cost"] + graph->getCost(wParent,node);
}

void 
Dijistra::addNodeToOpenList(WPtr<SearchNode> wNode)
{
  auto newNode = wNode.lock();
  for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
    auto node = it->lock();
    if(node->data["cost"] > newNode->data["cost"]){
      m_openList.insert(it,newNode);
      return;
    }
  }
  m_openList.push_back(newNode);
}

bool 
Dijistra::isBetterPath(WPtr<SearchNode> wNode, WPtr<SearchNode> wParent)
{
  if(wNode.expired() || wParent.expired()) return false;
  auto node = wNode.lock();
  auto parent = wParent.lock();
  auto graph = m_graph.lock();
  return node->data["cost"] > parent->data["cost"] + graph->getCost(wParent,node);
}

}

