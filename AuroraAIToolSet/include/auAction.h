/**
 * @file auAction.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"
#include "auWorldState.h"

namespace auToolSeetSDK{

class Action
{
 public:
  
  /**
   * @brief sets the precondicions to a world state 
   * @param ws 
  */
  void
  setPrecondicions(WorldState& ws);

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

 private:

  /**
   * @brief the things necesary for executing this action
  */
  WorldState m_preconditions;

  /**
   * @brief the changes that are the result of this action
  */
  WorldState m_effects;


};

}


