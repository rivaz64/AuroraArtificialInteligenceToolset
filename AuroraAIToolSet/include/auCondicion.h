#pragma once

#include "auWorldSituation.h"
#include "auGeneralRule.h"

namespace auToolSeetSDK
{

namespace INTERACTION_RESULT
{
enum E{
  kImposible,
  kFailed,
  kSuccesfull
};
}

class AU_UTILITY_EXPORT Condicion
{
public:

  Condicion() = default;

  Condicion(GeneralRule* rule,
         Vector<int>&& precondicion,
         Vector<CharacterChange>&& atributes
         ) :
    m_rule(rule),
    m_precondicion(precondicion),
    m_atributes(atributes)
  {}

  INTERACTION_RESULT::E
  tryInteraction(WorldSituation& ws, Vector<SPtr<Thing>>& things);

 private:

  GeneralRule* m_rule;
  Vector<int> m_precondicion;
  Vector<CharacterChange> m_atributes;
};
}


