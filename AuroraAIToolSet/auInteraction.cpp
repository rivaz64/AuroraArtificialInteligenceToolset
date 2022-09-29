#include "auInteraction.h"
#include "auSituation.h"
namespace auToolSeetSDK
{

INTERACTION_RESULT::E
Interaction::doInteraction(WorldSituation& ws, Vector<SPtr<Thing>> characters)
{
  auto result = m_condicion.tryInteraction(ws,characters);
  if(result == INTERACTION_RESULT::kSuccesfull){
    m_succesful.apply(ws);
  }
  else if(result == INTERACTION_RESULT::kFailed){
    m_failed.apply(ws);
  }
  return result;
}

}

