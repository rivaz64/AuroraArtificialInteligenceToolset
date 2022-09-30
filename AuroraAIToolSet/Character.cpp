#include "auCharacter.h"

namespace auToolSeetSDK
{

float 
Character::getGeneralPasion(const String& pasion)
{
  if(m_pasions.find(pasion) == m_pasions.end()){
    return 1;
  }

  float ans = 0;
  for(auto p : m_pasions[pasion]){
    ans += p.second;
  }
  return ans/static_cast<float>(m_pasions[pasion].size());
}

float 
Character::getGeneralPerception(const String& name)
{
  float ans = 0;
  float numOfPasions = 0;
  for(auto pasion : m_pasions){
    if(pasion.second.find(name) != pasion.second.end()){
      numOfPasions+=1;
      ans += pasion.second[name];
    }
  }
  if(numOfPasions == 0){
    return 1;
  }
  return ans/numOfPasions;
}

float 
Character::getPasionFrom(const String& pasion, const String& name)
{
  if(m_pasions.find(pasion) == m_pasions.end()){
    return 1;
  }
  if(m_pasions[pasion].find(name) == m_pasions[pasion].end()){
    return 1;
  }
  return m_pasions[pasion][name];
}

void 
Character::setPasionTo(const String& pasion, const String& name, float change)
{
  if(m_pasions.find(pasion) == m_pasions.end()){
    m_pasions.insert({pasion,{}});
  }
  if(m_pasions[pasion].find(name) == m_pasions[pasion].end()){
    m_pasions[pasion].insert({name,1.f});
  }
  m_pasions[pasion][name] += change;
}

}
