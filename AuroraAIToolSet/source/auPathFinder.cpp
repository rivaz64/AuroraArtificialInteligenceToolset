#include "auPathFinder.h"
#include "auSearchGraph.h"

namespace auToolSeetSDK
{

void
PathFinder::reset()
{
  m_openList.clear();
  m_nodes.clear();
  m_path.clear();
}

SEARCH_STATE::E
PathFinder::step()
{
  if(!canContinueSearching()){
    return SEARCH_STATE::kFailed;
  }
  auto wNode = getNextNodeForSearch();
  if(wNode.expired()){
    return SEARCH_STATE::kFailed;
  }
  auto actualNode = wNode.lock();
  if(m_graph->isAtGoal(actualNode->id,m_goalId)){
    makePath(actualNode);
    return SEARCH_STATE::kPathFinded;
  }
  auto adjacents = m_graph->getAdjacentNodes(actualNode->id);
  for(auto& adjacentId : adjacents){
    WPtr<SearchNode> adjacentNode;
    for(auto& otherNode : m_nodes){
      if(otherNode->id == adjacentId){
        adjacentNode = otherNode;
      }
    }
    if(adjacentNode.expired()){
      addNode(adjacentId,actualNode);
    }
    else{
      analizeNode(adjacentNode,actualNode);
    }
    //else if(isBetterPath(adjacentNode,actualNode)){
    //  //auto it = find(m_openList.begin(),m_openList.end(),adjacentId);
    //  //if(it != m_openList.end()){
    //  //  m_openList.erase(it);
    //  //}
    //  
    //}
  }
  return SEARCH_STATE::kSearching;
}

bool 
PathFinder::canContinueSearching()
{
  return !m_openList.empty();
}

WPtr<SearchNode> 
PathFinder::getNextNodeForSearch()
{
  auto node = *m_openList.begin();
  m_openList.pop_front();
  return node;
}

void 
PathFinder::makePath(WPtr<SearchNode> lastNode)
{
  auto wNode = lastNode;
  while(!wNode.expired()){
    auto node = wNode.lock();
    m_path.push_back(node->id);
    wNode = node->parent;
  }
}

void 
PathFinder::addNode(uint32 newNodeId, WPtr<SearchNode> parentNode)
{
  auto newNode = makeSPtr<SearchNode>();
  newNode->id = newNodeId;
  newNode->parent = parentNode;
  addDataToNode(newNode);
  //newNode->heuristic = m_graph->getHeuristicDistance(newNode);
  //m_graph->getCost(parentNode,newNode);
  m_nodes.push_back(newNode);
  addNodeToOpenList(newNode);
}

}

