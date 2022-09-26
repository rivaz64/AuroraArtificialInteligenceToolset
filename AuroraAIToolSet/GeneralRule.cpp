#include "auGeneralRule.h"
#include "auAlgorithms.h"
namespace auToolSeetSDK
{

Vector<SPtr<Thing>>
GeneralRule::getAllsolved(SituationDescriptor& situation)
{
  Vector<SPtr<Thing>> ans;
  for(auto val : situation.variables){
    if(contains(m_foundValues,val)){
      ans.push_back(m_finalThings[val]);
    }
  }
  return ans;
}

void
GeneralRule::solveDirectly(
  WorldSituation& ws, 
  int variableId, 
  Vector<SituationDescriptor>& situationsIsIn)
{
  for(auto& situationDes : situationsIsIn){
    auto things = getAllsolved(situationDes);
    if(things.size()+1 == situationDes.variables.size()){
      auto similar = ws.getAllSimilar(situationDes.id,things);
      if(similar.size() >= 1){
        auto foundValue = notIntersection(things,similar[0].m_things)[0];
        m_finalThings[variableId] = foundValue;
        m_foundValues.push_back(variableId);
        //erase(m_unknownValues,variableId);
        auto pos = find(m_unknownValues.begin(),m_unknownValues.end(),variableId);
        m_unknownValues.erase(pos);
      }
    }
  }
}

Vector<SituationDescriptor>
GeneralRule::getAllSituationsWithVariable(int variableId)
{
  Vector<SituationDescriptor> ans;
  for(auto& situation : m_precondicions){
    if(contains(m_situations[situation].variables,variableId)){
      ans.push_back(m_situations[situation]);
    }
  }
  return ans;
}

void 
GeneralRule::findUnknownValues(WorldSituation& ws)
{
  for(auto unknownValueId : m_unknownValues){
    auto situations = getAllSituationsWithVariable(unknownValueId);

    solveDirectly(ws,unknownValueId,situations);
  }
}

bool 
GeneralRule::solve(WorldSituation& ws, Vector<SPtr<Thing>>& things,Vector<int>& precondicions)
{
  int inputs = m_inputVariables.size();
  AU_ASSERT(things.size() == inputs);
  m_finalThings.resize(m_numOfVariables);
  m_foundValues = m_inputVariables;
  m_precondicions = precondicions;
  for(int i = 0; i<inputs; ++i){
    m_finalThings[m_inputVariables[i]] = things[i];
  }

  for(int i = 0; i<m_numOfVariables; ++i){
    if(!contains(m_inputVariables,i)){
      m_unknownValues.push_back(i);
    }
  }

  findUnknownValues(ws);

  return m_unknownValues.size()==0;
}

Vector<Situation>
GeneralRule::getSolvedSituations(const Vector<int>& situations)
{
  Vector<Situation> ans;
  for(auto situation : situations){
    Situation s;
    s.m_id = m_situations[situation].id;

    for(auto thing : m_situations[situation].variables){
      s.m_things.push_back(m_finalThings[thing]);
    }

    ans.push_back(s);
  }
  return ans;
}

}

