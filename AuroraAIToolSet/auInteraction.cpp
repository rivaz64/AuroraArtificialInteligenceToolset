#include "auInteraction.h"
#include "auSituation.h"
namespace auToolSeetSDK
{

bool 
Interaction::canDoInteraction(const WorldSituation& ws, Thing character)
{ 
  AU_ASSERT(character.type == THING_TYPE::kCharacter);

  //return ws.isTrue(m_precondicion.getSituation({character}));
  return false;
}

void
Interaction::doInteraction(WorldSituation& ws, Vector<SPtr<Thing>> characters)
{
  auto result = m_condicion.tryInteraction(ws,characters);
  if(result == INTERACTION_RESULT::kSuccesfull){
    m_succesful.apply(ws);
  }
  else if(result == INTERACTION_RESULT::kFailed){
    m_failed.apply(ws);
  }
}

}

