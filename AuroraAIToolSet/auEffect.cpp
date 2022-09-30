#include "auEffect.h"
#include "auAlgorithms.h"
#include "auCharacter.h"
namespace auToolSeetSDK
{
void
Effect::apply(WorldSituation& ws)
{
  //auto situations = m_rule->getSolvedSituations(m_falseSituations);
  
  for(auto& situation : m_falseSituations){
    Situation solved;
    if(m_rule->getSolvedSituation(situation,solved))
    ws.lie(solved);
  }

  //situations = m_rule->getSolvedSituations(m_trueSituations);
  for(auto& situation : m_trueSituations){
    Situation solved;
    if(m_rule->getSolvedSituation(situation,solved))
    ws.add(solved);
  }

  for(auto change : m_changes){
    if(contains(m_rule->m_unknownValues,change.variableId) || contains(m_rule->m_unknownValues,change.character)) continue;

    auto thing = m_rule->m_finalThings[change.variableId];
    auto character = cast<Character>(m_rule->m_finalThings[change.character]);
    auto name = character->name;
    if(thing->type == THING_TYPE::kCharacter){
      cast<Character>(thing)->setPasionTo(change.atribute, name, change.value);
    }
  }
}
}
