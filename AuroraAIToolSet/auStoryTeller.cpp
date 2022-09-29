#include "auStoryTeller.h"
#include "auWorldSituation.h"
#include "auAlgorithms.h"
namespace auToolSeetSDK
{

void 
StoryTeller::step()
{
  INTERACTION_RESULT::E result;
  SPtr<Interaction> interaction;
  do{
    interaction = getRandom(m_interactions);
    uint32 n = interaction->getNumOfAtributes();

    Vector<SPtr<Thing>> characters;
    for(auto i = 0; i<n; ++i){
      auto character = getRandom(m_characters);
      while(contains(characters,character)) character = getRandom(m_characters);
      characters.push_back(character);
    }

    result = interaction->doInteraction(ws,characters);
  } while (result == INTERACTION_RESULT::kImposible);
  
  print(interaction->getString());

  print(ws.getString());
}

void
StoryTeller::playerAction(const String& interaction, const Vector<String>& names)
{
  Vector<SPtr<Thing>> characters;
  for(auto name : names){
    characters.push_back(m_characters[at(m_names,name)]);
  }

  auto i = m_interactions[at(m_interactionIds,interaction)];

  i->doInteraction(ws, characters);

  print(i->getString());

  print(ws.getString());
}



}

