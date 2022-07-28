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

  WorldState() = default;

  WorldState(Vector<Pair<uint32,bool>>&& properties);

  /**
   * @brief biulds the world state that has this id
   * @param id 
  */
  WorldState(uint32 id);

  FORCEINLINE bool 
  operator==(const WorldState& other) const
  {
    int32 difs = getNumOfDiferences(other);
    return difs == 0;
  }

  /**
   * @brief defines a condicion of the world
   * @param condicion 
  */
  static void
  defineCondicion(uint32 condicion);

  /**
   * @brief the function to know if a property is true or false
   * @param condicion 
   * @param function 
  */
  static void
  attachFunctionToCondicion(uint32 condicion, function<bool(void*)>&& function);

  static uint32
  getFlagPos(uint32 userFlag);

  /**
   * @brief gets the flag from the user defined
   * @param userFlag 
   * @return 
  */
  static uint32
  getFlag(uint32 userFlag);

  /**
   * @brief gets the current world state for a pawn
   * @param ws 
   * @param pawn 
  */
  static void
  getCurrentWorldState(WorldState& ws,void* pawn);

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
  getNumOfDiferences(const WorldState& other) const;

  /**
   * @brief the number of condicions of this state cares about that are satisfied in the 
   * other worldState
   * @param other 
   * @return 
  */
  uint32 
  getNumOfUnsatisfiedCondicion(const WorldState& other);

  /**
   * @brief if the other world state satisfies this one
   * @param other 
   * @return 
  */
  bool 
  satisfies(const WorldState& other);

  FORCEINLINE uint32
  getMask()
  {
    return m_mask;
  }

  FORCEINLINE void
  setMask(uint32 flagMask)
  {
    m_mask = flagMask;
  }

  FORCEINLINE void
  setCondicions(uint32 condicions)
  {
    m_condicions = condicions;
  }

  FORCEINLINE uint32
  getCondicions()
  {
    return m_condicions;
  }

  /**
   * @brief gets the id of this ws 
   * @return 
  */
  uint32
  getId();

 private:

  void
  setCondicionWithFlag(uint32 flag, bool isTrue); 

  /**
   * @brief pams the flag with user flags
   * first is the user flag
   * second is the world state flag 
  */
  static Vector<uint32> g_flagMapping;

  /**
   * @brief the functions to fill a world state
  */
  static Vector<function<bool(void*)>> g_condicionFiller;

  /**
   * @brief the condicions to concider in this world state
  */
  uint32 m_mask = 0;

  /**
   * @brief the condicions in the world that can be true or not
  */
  uint32 m_condicions;

  

  friend class Action;
};

}


