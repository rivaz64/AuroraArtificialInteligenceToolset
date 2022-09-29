#pragma once

#include "auWorldSituation.h"
#include "auGeneralRule.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT Effect
{
public:

  Effect() = default;

  Effect(
         Vector<int>&& trueSituations,
         Vector<int>&& falseSituations,
         Vector<CharacterChange>&& changes
         ) :
    m_trueSituations(trueSituations),
    m_falseSituations(falseSituations),
    m_changes(changes)
  {}

  Effect(GeneralRule* rule,
         Vector<int>&& trueSituations,
         Vector<int>&& falseSituations,
         Vector<CharacterChange>&& changes
         ) :
    m_rule(rule),
    m_trueSituations(trueSituations),
    m_falseSituations(falseSituations),
    m_changes(changes)
  {}

  void
  apply(WorldSituation& ws);

private:

  GeneralRule* m_rule;
  Vector<int> m_trueSituations;
  Vector<int> m_falseSituations;
  Vector<CharacterChange> m_changes;
  
  friend class Interaction;
};

}


