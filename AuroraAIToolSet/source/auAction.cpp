#include "auAction.h"

namespace auToolSeetSDK
{
bool
Action::validatePrecondicions(const WorldState& ws)
{
  return m_preconditions.satisfies(ws);
}

void
Action::applyEffects(WorldState& ws)
{
  ws.m_mask |= m_effects.m_mask;
  ws.m_condicions = (m_effects.m_mask&m_effects.m_condicions)|((~m_effects.m_mask)&ws.m_condicions);
}
bool 
Action::isCompleted(const WorldState& ws)
{
  return m_effects.satisfies(ws);
}

void 
Action::undo(WorldState& ws)
{
  ws.m_mask &= ~m_effects.m_mask;
  ws.m_mask |= m_preconditions.m_mask;
  ws.m_condicions = (m_preconditions.m_mask&m_preconditions.m_condicions)|((~m_preconditions.m_mask)&ws.m_condicions);
}

void
Action::solvePlanWSVariable(WorldState& currentWS, WorldState& goalWS)
{
  //auto mask = m_effects.m_flagMask&goalWS.m_flagMask;
  //currentWS.m_flagMask |= mask;
  //
  //currentWS.m_wordlStateFlags = (mask&goalWS.m_wordlStateFlags)|((!mask)&currentWS.m_wordlStateFlags);
}

void 
Action::setPlanWSPrecondicions(WorldState& goalWS)
{
  //goalWS.m_flagMask |= m_preconditions.m_flagMask;
  //goalWS.m_flagMask = (m_preconditions.m_flagMask&m_preconditions.m_wordlStateFlags)|((~m_preconditions.m_flagMask)&goalWS.m_wordlStateFlags);
}

}

