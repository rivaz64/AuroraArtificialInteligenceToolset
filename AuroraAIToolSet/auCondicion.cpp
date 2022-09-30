#include "auCondicion.h"
#include "auAlgorithms.h"
#include "auCharacter.h"


namespace auToolSeetSDK
{

INTERACTION_RESULT::E
Condicion::tryInteraction(WorldSituation& ws, Vector<SPtr<Thing>>& things)
{
  m_rule->solve(ws,things);
  
  //auto situations = m_rule->getSolvedSituations(m_truePrecondicion);
  for(auto& situation : m_truePrecondicion){
    Situation solved;
    if(m_rule->getSolvedSituation(situation,solved)){
      if(!ws.isTrue(solved)){
        return INTERACTION_RESULT::kImposible;
      }
    }
    else{
      return INTERACTION_RESULT::kImposible;
    }
  }

  for(auto& situation : m_falsePrecondicion){
    Situation solved;
    if(m_rule->getSolvedSituation(situation,solved)){
      if(!ws.isTrue(solved)){
        return INTERACTION_RESULT::kImposible;
      }
    }
    else{
      return INTERACTION_RESULT::kImposible;
    }
  }

  //situations = m_rule->getSolvedSituations(m_falsePrecondicion);
  //for(auto& situation : situations){
  //  if(ws.isTrue(situation)){
  //    return INTERACTION_RESULT::kImposible;
  //  }
  //}

  for(auto atribute : m_precondicionAtributes){
    auto value = abs(atribute.value);
    auto thing = m_rule->m_finalThings[atribute.variableId];
    auto name = cast<Character>(m_rule->m_finalThings[atribute.character])->name;
    if(thing->type == THING_TYPE::kCharacter){
      auto character = cast<Character>(thing);
      auto charValue = character->getPasionFrom(atribute.atribute,name);
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
    auto name = cast<Character>(m_rule->m_finalThings[atribute.character])->name;
    if(thing->type == THING_TYPE::kCharacter){
      auto character = cast<Character>(thing);
      auto charValue = character->getPasionFrom(atribute.atribute,name);
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

