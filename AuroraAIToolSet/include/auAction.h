/**
 * @file auAction.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auWorldState.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT Action
{
 public:
  
  Action() = default;

  Action(String&& name, float cost) :
    m_name(move(name)), m_cost(cost) {}

  /**
   * @brief sets the precondicions to a world state 
   * @param ws 
  */
  FORCEINLINE void
  setPrecondicions(WorldState& ws)
  {
    m_preconditions = ws;
  }

  FORCEINLINE void
  setEffects(WorldState& ws)
  {
    m_effects = ws;
  }

  FORCEINLINE void
  setPrecondicion(uint32 condicion, bool b)
  {
    m_preconditions.setCondicion(condicion,b);
  }

  FORCEINLINE void
  setEffect(uint32 condicion, bool b)
  {
    m_effects.setCondicion(condicion,b);
  }

  /**
   * @brief if in this world state the action can be executed
   * @param ws 
   * @return 
  */
  bool
  validatePrecondicions(const WorldState& ws);

  /**
   * @brief changes this world state at how it would be after executing this action
   * @param ws 
   * @return 
  */
  void
  applyEffects(WorldState& ws);

  /**
   * @brief if this action has been completed succesfully in the current world state
   * @param ws 
  */
  bool
  isCompleted(const WorldState& ws);

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
  execute() {}

  /**
   * @brief stops executing this action
  */
  virtual void
  deactivate() {}

  /**
   * @brief updates this action
  */
  virtual void
  update() {}

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

  FORCEINLINE String
  getName()
  {
    return m_name;
  }

 protected:

  /**
   * @brief to identify this action
  */
  String m_name;

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


