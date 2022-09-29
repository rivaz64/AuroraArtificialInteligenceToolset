#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK
{

namespace THING_TYPE{
enum E{
  kNone,
  kCharacter,
  kPlace,
  kItem
};
}

struct AU_UTILITY_EXPORT Thing
{ 
  Thing() :
    type(THING_TYPE::kNone), name(""), pointer(nullptr) {}

  Thing(THING_TYPE::E t, const String& n, void* p) :
    type(t), name(n), pointer(p) {}

  FORCEINLINE bool 
  operator==(const Thing& other) const
  {
    return 
      type == other.type &&
      name == other.name &&
      pointer == other.pointer;
  }

  FORCEINLINE bool 
  operator!=(const Thing& other) const
  {
    return !(*this == other);
  }

  THING_TYPE::E type;

  String name;

  void* pointer;

  FORCEINLINE String
  getString()
  {
    return name;
  }
};

class AU_UTILITY_EXPORT Situation
{
public:
  Situation() = default;

  Situation(const String& situationId, const Vector<SPtr<Thing>>& things);

  bool 
  operator==(const Situation& other) const;

  FORCEINLINE SIZE_T 
  getNumOfTypes() const
  {
    return m_things.size();
  }

  FORCEINLINE THING_TYPE::E
  getType(uint32 n) const
  {
    return m_situationsRegister[m_id][n];
  }

  FORCEINLINE SPtr<Thing>
  getValue(uint32 n) const
  {
    return m_things[n];
  }

  FORCEINLINE void
  setValue(uint32 n,SPtr<Thing> v)
  {
    AU_ASSERT(v->type == m_situationsRegister[m_id][n]);
    m_things[n] = v;
  }

  static void
  regist(const String& id,const Vector<THING_TYPE::E>& types);
  
  FORCEINLINE String
  getString()
  {
    if(m_things.size() == 1){
      return m_things[0]->getString() + " is " + m_id;
    }
    else{
      return m_things[0]->getString() + " " + m_id + " " + m_things[1]->getString();
    }
  }

public:
  String m_id;

  Vector<SPtr<Thing>> m_things;

  friend class WorldSituation;
  friend class Effect;
public:
  static Map<String,Vector<THING_TYPE::E>> m_situationsRegister;
};


}


