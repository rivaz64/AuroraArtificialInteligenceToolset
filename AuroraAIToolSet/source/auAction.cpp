#include "auAction.h"

namespace auToolSeetSDK
{

bool 
Action::canSolvePlan(WorldState& currentWS, WorldState& goalWS)
{
  auto mask = m_effects.getMask()&currentWS.getMask()&goalWS.getMask();
  auto condicions = mask&(currentWS.getWorldState()^goalWS.getWorldState());
  return condicions;
}

void
Action::solvePlanWSVariable(WorldState& currentWS, WorldState& goalWS)
{
  auto mask = m_effects.m_flagMask&goalWS.m_flagMask;
  currentWS.m_flagMask |= mask;

  currentWS.m_wordlStateFlags = (mask&goalWS.m_wordlStateFlags)|((!mask)&currentWS.m_wordlStateFlags);
}

void 
Action::setPlanWSPrecondicions(WorldState& goalWS)
{
  goalWS.m_flagMask |= m_preconditions.m_flagMask;
  goalWS.m_flagMask = (m_preconditions.m_flagMask&m_preconditions.m_wordlStateFlags)|((~m_preconditions.m_flagMask)&goalWS.m_wordlStateFlags);
}

}

