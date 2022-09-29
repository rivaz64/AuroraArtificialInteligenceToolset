#pragma once
#include "auPrerequisites.h"
#include "auInteraction.h"
#include "auCharacter.h"
namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT StoryTeller
{
public:

  void
  step();

  FORCEINLINE void
  addCharacter(String&& name, void* reference)
  {
    m_characters.push_back(makeSPtr<Character>(name,reference));
  }

  FORCEINLINE void
  addInteraction(String&& id, GeneralRule rule, Condicion condicion, Effect succesful, Effect failed)
  {
    m_interactions.push_back(makeSPtr<Interaction>(id,rule,condicion,succesful,failed));
  }

private:

  Vector<SPtr<Interaction>> m_interactions;

  Vector<SPtr<Thing>> m_characters;

  WorldSituation ws;
};

}


