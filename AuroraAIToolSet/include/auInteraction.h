#pragma once

#include "auPrerequisites.h"
#include "auWorldSituation.h"
#include "auGeneralRule.h"
#include "auEffect.h"
#include "auCondicion.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT Interaction
{
public:

  Interaction() = default;

  bool 
  canDoInteraction(const WorldSituation& ws, Thing character);

  void 
  doInteraction(WorldSituation& ws, Vector<SPtr<Thing>> characters);

  Condicion m_condicion;

  GeneralRule m_rule;

  Effect m_succesful, m_failed;
};

}


