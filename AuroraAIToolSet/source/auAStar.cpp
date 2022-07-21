#include "auAStar.h"
#include "auSearchGraph.h"


namespace auToolSeetSDK{

//void
//AStar::addNode(uint32 newNodeId, WPtr<AStarNode> parentNode)
//{
//  auto newNode = makeSPtr<AStarNode>();
//  newNode->id = newNodeId;
//  
//  m_graph->getCost(parentNode,newNode);
//  m_nodes.push_back(newNode);
//  addNodeToOpenList(newNode);
//}

void 
AStar::addDataToNode(WPtr<SearchNode> wNode)
{
  if(wNode.expired()) return;
  auto node = cast<AStarNode>(wNode.lock());
  node->heuristic = m_graph->getHeuristicDistance(node);
  node->toGoal = m_graph->getCost(node,node->parent);
}

void
AStar::addNodeToOpenList(WPtr<SearchNode> wNode)
{
  if(wNode.expired()){
    return;
  }
  auto node = cast<AStarNode>(wNode.lock());
  auto fitness = node->getFitness();
  for(auto it = m_openList.begin(); it != m_openList.end(); ++it){
    if(it->expired()) continue;
    auto otherNode = cast<AStarNode>(it->lock());
    if(fitness < otherNode->getFitness()){
      m_openList.insert(it,wNode);
    }
  }
}

void AStar::analizeNode(WPtr<SearchNode> wNode, WPtr<SearchNode> wNewParent)
{ 
  if(wNode.expired() || wNewParent.expired()) return;
  auto node = cast<AStarNode>(wNode.lock());
  auto newParent = cast<AStarNode>(wNewParent.lock());
  if(isBetterPath(node,newParent)){
    //auto it = find(m_openList.begin(),m_openList.end(),adjacentId);
    //  //if(it != m_openList.end()){
    //  //  m_openList.erase(it);
    //  //}
  }
}

bool 
AStar::isBetterPath(WPtr<AStarNode> wNode, WPtr<AStarNode> wNewParent)
{
  if(wNode.expired() || wNewParent.expired()) return false;

  auto node = wNode.lock();
  auto newParent = wNewParent.lock();

  float actualEuristic = m_graph->getHeuristicDistance(wNode);
  float newEuristic = m_graph->getCost(newParent,node) + node->heuristic;
  return newEuristic < actualEuristic;
}

}