#include "auSituation.h"
#include "auAlgorithms.h"
namespace auToolSeetSDK
{
Map<String,Vector<THING_TYPE::E>> Situation::m_situationsRegister;

bool
check(const String& situationId, const Vector<SPtr<Thing>>& things)
{
  auto numOfTypes = Situation::m_situationsRegister[situationId].size();
  if(things.size() != numOfTypes){
    print("incorrect size in " + situationId);
    return false;
  }
  for(int i = 0; i<numOfTypes; ++i){
    if(Situation::m_situationsRegister[situationId][i] != things[i]->type) return false;
  }
  return true;
}

Situation::Situation(const String& situationId, const Vector<SPtr<Thing>>& things) :
  m_id(situationId), m_things(things)
{
  AU_ASSERT(check(situationId,things));
}

bool 
Situation::operator==(const Situation& other) const
{
  auto numOfTypes = getNumOfTypes();
  if(m_id != other.m_id){
    return false;
  }
  return m_things == other.m_things;
}

//bool 
//Situation::operator!=(const Situation& other) const
//{
//  auto numOfTypes = getNumOfTypes();
//  if(m_id != other.m_id){
//    return true;
//  }
//  if(intersection(m_things,other.m_things).size() != numOfTypes){
//    return true;
//  }
//  return false;
//}

void 
Situation::regist(const String& id, const Vector<THING_TYPE::E>& types)
{
  m_situationsRegister.insert({id,types});
}
}
