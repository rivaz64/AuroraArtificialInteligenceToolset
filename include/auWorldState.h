/**
 * @file auWorldState.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK{

namespace WORLD_PROP_TYPE{
enum E
{
  kNone = 0,
  kBool,
  kInt,
  kFloat
};
}

namespace WORLD_PROP_KEY{
enum E
{
  kNone = 0
};
}

struct WorldProperty
{
  /**
   * @brief what this property represents
  */
  WORLD_PROP_KEY::E key;

  /**
   * @brief the type of this property
  */
  WORLD_PROP_TYPE::E type;

  /**
   * @brief the actual value of this property
  */
  union value
  {
    bool bValue;
    int iValue;
    float fValue;

  };
};

class AU_UTILITY_EXPORT WorldState
{
 public:

  /**
   * @brief defines a condicion of the world
   * @param condicion 
  */
  static void
  defineCondicion(uint32 condicion);

  /**
   * @brief add a condicion to concider
   * @param the condicion of the user
  */
  void
  addCondicion(uint32 condicion);

  /**
   * @brief checks if this world state considers this condicion
   * @param condicion 
   * @return 
  */
  bool
  hasCondicion(uint32 condicion);

  /**
   * @brief set a condicion as true or false
   * @param the condicion of the user
   * @param if ths condicion is set or not
  */
  void
  setCondicion(uint32 condicion, bool isTrue);

  /**
   * @brief gets if a condicion is true or false
   * @param condicion 
   * @return 
  */
  bool
  getCondicion(uint32 condicion);

  /**
   * @brief the number of diferences between 2 world states
   * @param other 
   * @return 
  */
  uint32 
  getNumOfDiferences(const WorldState& other);

  uint32 
  getNumOfUnsatisfiedCondicion(const WorldState& other);

  //FORCEINLINE uint32
  //getMask()
  //{
  //  return m_flagMask;
  //}
  //
  //FORCEINLINE uint32
  //getFlags()
  //{
  //  return m_wordlStateFlags;
  //}

  /**
   * @brief gets the flag from the user defined
   * @param userFlag 
   * @return 
  */
  static uint32
  getFlag(uint32 userFlag);

  FORCEINLINE void
  setMask(uint32 flagMask)
  {
    m_flagMask = flagMask;
  }

  FORCEINLINE void
  setWorldState(uint32 wordlState)
  {
    m_wordlStateFlags = wordlState;
  }

  FORCEINLINE uint32
  getMask()
  {
    return m_flagMask;
  }

  FORCEINLINE uint32
  getWorldState()
  {
    return m_wordlStateFlags;
  }

 private:

  /**
   * @brief pams the flag with user flags
   * first is the user flag
   * second is the world state flag 
  */
  static Vector<uint32> m_flagMapping;

  /**
   * @brief the condicions to concider in this world state
  */
  uint32 m_flagMask = 0;

  /**
   * @brief the condicions in the world that can be true or not
  */
  uint32 m_wordlStateFlags;

  friend class Action;
};

}


