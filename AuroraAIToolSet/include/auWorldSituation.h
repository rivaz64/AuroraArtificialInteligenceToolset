#pragma once

#include "auPrerequisites.h"
#include "auSituation.h" 

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT WorldSituation
{
public:
  FORCEINLINE void
  add(const Situation& newSituation)
  {
    m_situations.push_back(newSituation);
  }
  
  FORCEINLINE void
  lie(const Situation& oldSituation)
  {
    auto pos = find(m_situations.begin(),m_situations.end(),oldSituation);
    if(pos != m_situations.end())
    m_situations.erase(pos);
  }

  FORCEINLINE bool
  isTrue(const Situation& s) const
  {
    return find(m_situations.begin(),m_situations.end(),s) != m_situations.end();
  }

  Vector<Situation>
  getAllSimilar(const String& situationId, const Vector<SPtr<Thing>>& things);

  FORCEINLINE String
  getString()
  {
    String ans;
    for(auto& situation : m_situations){
      ans += situation.getString() + '\n';
    }
    return ans;
  }

private:
  Vector<Situation> m_situations;
};

}


