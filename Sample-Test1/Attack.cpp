#include "pch.h"
#include "Attack.h"
#include "Flags.h"

namespace auToolSeetSDK
{

Attack::Attack(uint32 weaponType, uint32 weaponRange)
{
  setPrecondicions(WorldState({{weaponType,true},
                               {weaponRange,true}}));

  setEffects(WorldState({{ENEMY_DEAD,true}}));
}

}

