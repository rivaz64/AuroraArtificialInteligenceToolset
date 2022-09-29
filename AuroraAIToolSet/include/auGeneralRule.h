#pragma once

#include "auWorldSituation.h"
namespace auToolSeetSDK
{
struct AU_UTILITY_EXPORT SituationDescriptor
{
  SituationDescriptor(const String& s, const Vector<int>& v) :
    id(s), variables(v) {}
  String id;
  Vector<int> variables;
};

struct AU_UTILITY_EXPORT CharacterChange
{
  CharacterChange(const String& s, float vc, int id) :
    atribute(s), value(vc), variableId(id){}
  String atribute;
  float value;
  int variableId;
};

class AU_UTILITY_EXPORT GeneralRule
{
public:
  GeneralRule() = default;

  GeneralRule(
    const Vector<SituationDescriptor>& newSituations,
    const Vector<int> inputVariables,
    int numOfVariables
    ) :
    m_inputVariables(inputVariables),
    m_situations(newSituations),
    m_numOfVariables(numOfVariables){}

  bool
  solve(WorldSituation& ws, Vector<SPtr<Thing>>& things,Vector<int>& precondicions);

  Vector<Situation>
  getSolvedSituations(const Vector<int>& situations);

private:

  void
  findUnknownValues(WorldSituation& ws);

  Vector<SituationDescriptor>
  getAllSituationsWithVariable(int variableId);

  void
  solveDirectly(
    WorldSituation& ws, 
    int variableId, 
    Vector<SituationDescriptor>& situationsIsIn);

  Vector<SPtr<Thing>>
  getAllsolved(SituationDescriptor& situation);

public:
  Vector<SituationDescriptor> m_situations;
  Vector<int> m_inputVariables;
  Vector<int> m_foundValues;
  Vector<int> m_unknownValues;
  Vector<int> m_precondicions;
  Vector<SPtr<Thing>> m_finalThings;
  int m_numOfVariables;
};
}




