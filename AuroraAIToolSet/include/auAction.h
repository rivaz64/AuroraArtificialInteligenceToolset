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

 private:

  /**
   * @brief the things necesary for executing this action
  */
  WorldState precondicion;

  /**
   * @brief the changes that are the result of this action
  */
  WorldState effects;


};

}


