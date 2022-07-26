/**
 * @file auAction.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once
#include "auAction.h"

namespace auToolSeetSDK{

class Attack :
  public Action
{
 public:

  Attack(uint32 weaponType, uint32 weaponRange);

 protected:
  uint32 m_weaponType;
  uint32 m_weaponRange;

};

}