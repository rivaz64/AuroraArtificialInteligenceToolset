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

  Interaction(String&& id) :
    m_id(id) {}

  Interaction(String& id, GeneralRule rule, Condicion condicion, Effect succesful, Effect failed) :
    m_id(id) ,m_rule(rule), m_condicion(condicion), m_succesful(succesful), m_failed(failed)
  {
    m_condicion.m_rule = &m_rule;
    m_succesful.m_rule = &m_rule;
    m_failed.m_rule = &m_rule;
  }

  INTERACTION_RESULT::E 
  doInteraction(WorldSituation& ws, Vector<SPtr<Thing>> characters);

  FORCEINLINE uint32
  getNumOfAtributes()
  {
    return m_rule.m_inputVariables.size();
  }

  FORCEINLINE String
  getString()
  {
    if(m_rule.m_inputVariables.size() == 1){
      return m_rule.m_finalThings[m_rule.m_inputVariables[0]]->getString() + " has " + m_id;
    }
    else{
      return m_rule.m_finalThings[m_rule.m_inputVariables[0]]->getString() + " has " + m_id + 
    " to " + m_rule.m_finalThings[m_rule.m_inputVariables[1]]->getString();
    }
  }

  String m_id;

  GeneralRule m_rule;

  Condicion m_condicion;

  Effect m_succesful, m_failed;
};

}


