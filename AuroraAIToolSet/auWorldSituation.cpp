#include "auWorldSituation.h"
#include "auAlgorithms.h"
#include "auInteraction.h"
namespace auToolSeetSDK
{

Vector<Situation>
WorldSituation::getAllSimilar(const String& situationId, const Vector<SPtr<Thing>>& things)
{
  Vector<Situation> ans;
  for(auto& situation : m_situations){
    if(situation.m_id == situationId){
      bool areSimilar = true;
      if(intersection(situation.m_things,things).size()>0){
        ans.push_back(situation);
      }
    }
  }
  return ans;
}


}

