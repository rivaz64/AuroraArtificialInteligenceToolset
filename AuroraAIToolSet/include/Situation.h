#pragma once

#include "auPrerequisites.h"

namespace auToolSeetSDK
{

namespace THING_TYPE
{
enum E{
  kCharacter,
  kPlace,
  kItem
};
}

class Situation
{
public:
  Situation() = default;

  Situation(const String& situationId, const Vector<THING_TYPE::E>& types);

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
    return m_things[n].first;
  }

  FORCEINLINE void*
  getValue(uint32 n) const
  {
    return m_things[n].second;
  }

  FORCEINLINE void
  setValue(uint32 n, void* v)
  {
    m_things[n].second = v;
  }

private:
  String m_situationId;

  Vector<pair<THING_TYPE::E,void*>> m_things;
};

}


