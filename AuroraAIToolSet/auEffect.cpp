#include "auEffect.h"
#include "auAlgorithms.h"
#include "auCharacter.h"
namespace auToolSeetSDK
{
void
Effect::apply(WorldSituation& ws)
{
  auto situations = m_rule->getSolvedSituations(m_falseSituations);
  for(auto& situation : situations){
    ws.lie(situation);
  }

  situations = m_rule->getSolvedSituations(m_trueSituations);
  for(auto& situation : situations){
    ws.add(situation);
  }

  for(auto change : m_changes){
    auto thing = m_rule->m_finalThings[change.variableId];
    if(thing->type == THING_TYPE::kCharacter){
      cast<Character>(thing)->m_atributes[change.atribute] += change.value;
    }
  }
}
}
