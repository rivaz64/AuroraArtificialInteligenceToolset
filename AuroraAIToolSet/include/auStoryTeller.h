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

  void
  playerAction(const String& interaction, const Vector<String>& names);

  FORCEINLINE void
  addCharacter(String&& name, void* reference)
  {
    m_characters.push_back(makeSPtr<Character>(name,reference));
    m_names.push_back(name);
  }

  FORCEINLINE void
  addInteraction(String&& id, GeneralRule rule, Condicion condicion, Effect succesful, Effect failed)
  {
    m_interactionIds.push_back(id);
    m_interactions.push_back(makeSPtr<Interaction>(id,rule,condicion,succesful,failed));
  }

  void
  represent(SPtr<Interaction> interaction);

public:

  Vector<String> m_interactionIds;
  Vector<String> m_names;

  Vector<SPtr<Interaction>> m_interactions;

  Vector<SPtr<Thing>> m_characters;

  WorldSituation ws;
};

}


