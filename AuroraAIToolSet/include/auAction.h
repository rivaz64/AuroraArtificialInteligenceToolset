/**
 * @file auAction.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auWorldState.h"

namespace auToolSeetSDK{

class AU_UTILITY_EXPORT Action
{
 public:
  
  /**
   * @brief sets the precondicions to a world state 
   * @param ws 
  */
  FORCEINLINE void
  setPrecondicions(WorldState& ws)
  {
    m_preconditions = ws;
  }

  /**
   * @brief si esta accoon va a resolver cualquiera de las condiciones
   * @param currentWS 
   * @param goalWS 
   * @return 
  */
  bool
  canSolvePlan(WorldState& currentWS, WorldState& goalWS);

  /**
   * @brief solves a world state to how it would be before executing the action
   * @param currentWS 
   * @param goalWS 
  */
  void
  solvePlanWSVariable(WorldState& currentWS, WorldState& goalWS);

  /**
   * @brief 
   * @param currentWS 
   * @param goalWS 
  */
  void
  setPlanWSPrecondicions(WorldState& goalWS);

  /**
   * @brief initializes the action at the begining 
  */
  virtual void
  init(){}

  /**
   * @brief starts executing this action
  */
  virtual void
  activation() {}

  /**
   * @brief stops executing this action
  */
  virtual void
  deactivate() {}

  /**
   * @brief if the actions has been succesfully completed
   * @return 
  */
  virtual bool
  completed() {return false;}

  FORCEINLINE WorldState&
  getPrecondicions()
  {
    return m_preconditions;
  }

  FORCEINLINE WorldState&
  getEffects()
  {
    return m_effects;
  }

  FORCEINLINE float
  getCost()
  {
    return m_cost;
  }

 private:

  /**
   * @brief the things necesary for executing this action
  */
  WorldState m_preconditions;

  /**
   * @brief the changes that are the result of this action
  */
  WorldState m_effects;

  /**
   * @brief howmuch it costs to dothis action
  */
  float m_cost;


};

}


