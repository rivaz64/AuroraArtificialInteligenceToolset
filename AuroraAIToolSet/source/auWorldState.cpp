#include "auWorldState.h"

namespace auToolSeetSDK{

Vector<uint32> WorldState::m_flagMapping = {};

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
  m_flagMapping.push_back(condicion);
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
  m_mask |= flag;
  if(isTrue){
    m_condicions |= flag;
  }
  else{
    m_condicions = (m_condicions^flag)&(~flag);
  }
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

uint32 
WorldState::getFlag(uint32 userFlag)
{
  auto flagPos = find(m_flagMapping.begin(),m_flagMapping.end(),userFlag)-m_flagMapping.begin();
  return 1<<flagPos;
}

}

