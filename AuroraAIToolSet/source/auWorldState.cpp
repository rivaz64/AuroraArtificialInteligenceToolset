#include "auWorldState.h"

namespace auToolSeetSDK{

Vector<uint32> WorldState::c_flagMapping = {};
Vector<function<bool(void*)>> WorldState::c_condicionFiller = {};

uint32
countBitsOn(uint32 flag)
{
  uint32 numOfBits = 0;
  for(SIZE_T i = 0; i<32; ++i){
    uint32 actualflag = 1<<i;
    if(actualflag&flag){
      ++numOfBits;
    }
  }
  return numOfBits;
}

void 
WorldState::defineCondicion(uint32 condicion)
{
  c_flagMapping.push_back(condicion);
  c_condicionFiller.resize(c_flagMapping.size());
}

void 
WorldState::attachFunctionToCondicion(uint32 condicion, function<bool(void*)>&& function)
{
  auto flagPos = getFlagPos(condicion);
  c_condicionFiller[flagPos] = move(function);
}

uint32 
WorldState::getFlagPos(uint32 userFlag)
{
  auto flagPos = find(c_flagMapping.begin(),c_flagMapping.end(),userFlag)-c_flagMapping.begin();
  return flagPos;
}

uint32
WorldState::getFlag(uint32 userFlag)
{
  return 1<<getFlagPos(userFlag);
}

void
WorldState::getCurrentWorldState(WorldState& ws, void* pawn)
{
  uint32 mask = ws.getMask();
  for(SIZE_T i = 0; i<32; ++i){
    uint32 actualflag = 1<<i;
    if(actualflag&mask){
      ws.setCondicionWithFlag(actualflag,c_condicionFiller[i](pawn));
    }
  };
}

void
WorldState::addCondicion(uint32 condicion)
{ 
  auto flag = getFlag(condicion);
  m_mask |= flag;
}

bool 
WorldState::hasCondicion(uint32 condicion)
{
  auto flag = getFlag(condicion);
  return flag & m_mask;
}

void 
WorldState::setCondicion(uint32 condicion, bool isTrue)
{
  auto flag = getFlag(condicion);
  setCondicionWithFlag(flag,isTrue);
}

bool 
WorldState::getCondicion(uint32 condicion)
{
  auto flag = getFlag(condicion);
  return flag&m_condicions;
}

uint32 
WorldState::getNumOfDiferences(const WorldState& other) const
{
  uint32 diferences = ((other.m_condicions^m_condicions)&
                       (other.m_mask&m_mask))|
                      (other.m_mask^m_mask);

  return countBitsOn(diferences);
}

uint32
WorldState::getNumOfUnsatisfiedCondicion(const WorldState& other)
{
  uint32 unsatisfied = m_mask&(
                        ~other.m_mask|(
                          other.m_mask&(
                            m_condicions^other.m_condicions
                          )
                        )
                       );
  return countBitsOn(unsatisfied);
}

bool 
WorldState::satisfies(const WorldState& other)
{
  return getNumOfUnsatisfiedCondicion(other)==0;
}


void 
WorldState::setCondicionWithFlag(uint32 flag, bool isTrue)
{
  m_mask |= flag;
  if(isTrue){
    m_condicions |= flag;
  }
  else{
    m_condicions = (m_condicions^flag)&(~flag);
  }
}
}

