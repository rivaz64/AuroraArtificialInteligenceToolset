#include "auPathFinder.h"
#include "auSearchGraph.h"

#include "auPlansGraph.h"
#include "auPlan.h"

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
  if(m_graph.expired()) return SEARCH_STATE::kFailed;

  auto graph = m_graph.lock();
  if(!canContinueSearching()){
    return SEARCH_STATE::kFailed;
  }
  auto wNode = getNextNodeForSearch();
  //printPath(wNode);
  if(wNode.expired()){
    return SEARCH_STATE::kFailed;
  }
  auto actualNode = wNode.lock();
  if(graph->isAtGoal(actualNode,m_goalId)){
    makePath(actualNode);
    return SEARCH_STATE::kPathFinded;
  }

  auto adjacents = graph->getAdjacentNodes(actualNode);
  for(auto& adjacent : adjacents){
    WPtr<SearchNode> adjacentNode;

    for(auto& otherNode : m_nodes){
      if(otherNode->id == adjacent->id){
        adjacentNode = otherNode;
      }
    }

    //if it has not been searched before
    if(adjacentNode.expired()){
      addNode(adjacent,actualNode);
    }

    //if this other path is better
    else if(isBetterPath(adjacentNode,actualNode)){
      auto it = m_openList.begin();
      for(;it != m_openList.end(); ++it){
        if(it->lock()->id == adjacentNode.lock()->id){
          break;
        }
      }
      if(it != m_openList.end()){
        m_openList.erase(it);
      }
      addDataToNode(adjacentNode,actualNode);
      addNodeToOpenList(adjacentNode);
    }
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
    m_path.push_back(node);
    wNode = node->parent;
  }
  m_path.pop_back();
}

void 
PathFinder::addNode(SPtr<SearchNode> newNode, WPtr<SearchNode> parentNode)
{
  newNode->parent = parentNode;
  addDataToNode(newNode,parentNode);
  m_nodes.push_back(newNode);
  addNodeToOpenList(newNode);
}

bool 
PathFinder::isBetterPath(WPtr<SearchNode> node, WPtr<SearchNode> newParent)
{
  return false;
}

void 
PathFinder::printPath(WPtr<SearchNode> node)
{
  auto wNode = node;
  Vector<WPtr<SearchNode>> path;
  while(!wNode.expired()){
    auto node = wNode.lock();
    path.push_back(node);
    wNode = node->parent;
  }
  path.pop_back();
  std::reverse(path.begin(),path.end());

  //for(auto& action : path){
  //  print(std::to_string(action.lock()->data["cost"]));
  //}

  auto plan = cast<PlansGraph>(m_graph.lock())->getPlan(path);

  //for(auto& action : plan->m_actions){
  //  print(action.lock()->getName());
  //}
  //print("");
}

}

