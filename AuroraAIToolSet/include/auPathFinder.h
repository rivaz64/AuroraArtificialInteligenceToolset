/**
 * @file auPathFinder.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK
{

/**
 * @brief nodes used for the search
*/
struct SearchNode{
  /**
   * @brief the id of the node
  */
  uint32 id;

  /**
   * @brief the node that found this one
  */
  WPtr<SearchNode> parent;
};

namespace SEARCH_STATE{
enum E{
kFailed = 0,
kSearching,
kPathFinded 
};
}

/**
 * @brief interface cass for all types of searches
*/
class AU_UTILITY_EXPORT PathFinder
{
 public:

  /**
   * @brief sets the node for the start of the search
  */
  FORCEINLINE void
  setSourceId(uint32 sourceId)
  {
    m_sourceId = sourceId;
  }

  /**
   * @brief sets the node that is the goal of the search
  */
  FORCEINLINE void
  setGoalId(uint32 goalId)
  {
    m_goalId = goalId;
  }

  FORCEINLINE Vector<uint32>
  getPath()
  {
    return m_path;
  }

  FORCEINLINE void
  setGraph(WPtr<SearchGraph> graph)
  {
    m_graph = graph;
  }

  /**
   * @brief 
   * @param  
  */
  FORCEINLINE SEARCH_STATE::E
  run()
  {
    reset();
    addNode(m_sourceId,WPtr<SearchNode>());
    auto actualState = SEARCH_STATE::kSearching;
    while(actualState == SEARCH_STATE::kSearching){
      actualState = step();
    }
    return actualState;
  }

  /**
   * @brief clears the data and prepares it for a new search
  */
  void
  reset();

  /**
   * @brief executes a step of the search.
   * @return the state of the search at the end of the state
  */
  SEARCH_STATE::E 
  step();

  /**
   * @brief if there is something els to search in
   * @return 
  */
  bool
  canContinueSearching();

  /**
   * @brief gets a node to do a search at
   * @return 
  */
  WPtr<SearchNode> 
  getNextNodeForSearch();

 protected:

  /**
   * @brief adds the nesesary data for the path find
   * @param node 
  */
  virtual void
  addDataToNode(WPtr<SearchNode> node){}

  /**
   * @brief after geting to the end it finds the path backwards
   * @param id 
  */
  void
  makePath(WPtr<SearchNode> lastNode);

  /**
   * @brief adds a node to the search
   * @param nodeId tthe node to be added
  */
  void 
  addNode(uint32 newNodeId, WPtr<SearchNode> parentNode);

  /**
   * @brief adds the node to the open list
   * @param newId the id of the node to add
  */
  virtual void
  addNodeToOpenList(WPtr<SearchNode> node) {}
  
  /**
   * @brief chooses what to do when finds a node that has been searched at
   * @param node 
  */
  virtual void
  analizeNode(WPtr<SearchNode> node, WPtr<SearchNode> newParent) {}

  /**
   * @brief from where to start the search
  */
  uint32 m_sourceId;

  /**
   * @brief where the search has to end
  */
  uint32 m_goalId;

  /**
   * @brief the graph to do the search in
  */
  WPtr<SearchGraph> m_graph;

  /**
   * @brief all the search Nodes
  */
  Vector<SPtr<SearchNode>> m_nodes;

  /**
   * @brief the path of id nodes
  */
  Vector<uint32> m_path;

  /**
   * @brief the paths in wait for search
  */
  List<WPtr<SearchNode>> m_openList;
};

}


