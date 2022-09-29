#include "auInteraction.h"
#include "auSituation.h"
#include "auCharacter.h"
namespace auToolSeetSDK
{

INTERACTION_RESULT::E
Interaction::doInteraction(WorldSituation& ws, Vector<SPtr<Thing>> characters)
{
  INTERACTION_RESULT::E result;
  result = m_condicion.tryInteraction(ws,characters);

  if(result == INTERACTION_RESULT::kImposible) return result;

  if(characters.size()>1 && cast<Character>(characters[1])->name == "player"){
    result = waitForPlayersResponse(cast<Character>(characters[0])->name);
  }
  
  if(result == INTERACTION_RESULT::kSuccesfull){
    m_succesful.apply(ws);
  }
  else if(result == INTERACTION_RESULT::kFailed){
    m_failed.apply(ws);
  }
  return result;
}

INTERACTION_RESULT::E 
Interaction::waitForPlayersResponse(String& name)
{
  print(name + " wants to " + m_id + " with you");
  string ans;
  std::cin >> ans;
  if(ans == "y"){
    return INTERACTION_RESULT::kSuccesfull;
  }
  if(ans == "n"){
    return INTERACTION_RESULT::kFailed;
  }
}

}

