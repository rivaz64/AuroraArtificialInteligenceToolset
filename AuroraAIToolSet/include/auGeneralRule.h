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
  CharacterChange(const String& s,int id, int n, float vc) :
    atribute(s), character(n), value(vc), variableId(id){}
  String atribute;
  int variableId;
  int character;
  float value;
  
};

class AU_UTILITY_EXPORT GeneralRule
{
public:
  GeneralRule() = default;

  GeneralRule(
    const Vector<SituationDescriptor>& newSituations,
    const Vector<int> inputVariables,
    const Vector<int> situationsForSolve,
    int numOfVariables
    ) :
    m_situations(newSituations),
    m_inputVariables(inputVariables),
    m_situationsForSolve(situationsForSolve),
    m_numOfVariables(numOfVariables){}

  bool
  solve(WorldSituation& ws, Vector<SPtr<Thing>>& things);

  bool
  getSolvedSituation(int situationId, Situation& situation);

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
  Vector<int> m_situationsForSolve;
  Vector<int> m_foundValues;
  Vector<int> m_unknownValues;
  Vector<SPtr<Thing>> m_finalThings;
  int m_numOfVariables;
};
}




