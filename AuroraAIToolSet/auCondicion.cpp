#include "auCondicion.h"
#include "auAlgorithms.h"
#include "auCharacter.h"


namespace auToolSeetSDK
{

INTERACTION_RESULT::E
Condicion::tryInteraction(WorldSituation& ws, Vector<SPtr<Thing>>& things)
{
  if(!m_rule->solve(ws,things,m_truePrecondicion)) return INTERACTION_RESULT::kImposible;

  auto situations = m_rule->getSolvedSituations(m_truePrecondicion);
  for(auto& situation : situations){
    if(!ws.isTrue(situation)){
      return INTERACTION_RESULT::kImposible;
    }
  }

  situations = m_rule->getSolvedSituations(m_falsePrecondicion);
  for(auto& situation : situations){
    if(ws.isTrue(situation)){
      return INTERACTION_RESULT::kImposible;
    }
  }

  for(auto atribute : m_precondicionAtributes){
    auto value = abs(atribute.value);
    auto thing = m_rule->m_finalThings[atribute.variableId];

    if(thing->type == THING_TYPE::kCharacter){
      auto character = cast<Character>(thing);
      auto charValue = character->m_atributes[atribute.atribute];
      if(!(
        (atribute.value > 0.0f && charValue > value) ||
        (atribute.value < 0.0f && charValue < value))
        )
      {
        return INTERACTION_RESULT::kImposible;
      }
    }
  }

  for(auto atribute : m_atributes){
    auto value = abs(atribute.value);
    auto thing = m_rule->m_finalThings[atribute.variableId];

    if(thing->type == THING_TYPE::kCharacter){
      auto character = cast<Character>(thing);
      auto charValue = character->m_atributes[atribute.atribute];
      if(!(
        (atribute.value > 0.0f && charValue > value) ||
        (atribute.value < 0.0f && charValue < value))
        )
      {
        return INTERACTION_RESULT::kFailed;
      }
    }
  }

  return INTERACTION_RESULT::kSuccesfull;
}

}

