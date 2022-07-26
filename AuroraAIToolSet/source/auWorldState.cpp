#include "auWorldState.h"

namespace auToolSeetSDK{

Vector<uint32> WorldState::m_flagMapping = {};

uint32
countBitsOn(uint32 flag)
{
  uint32 numOfBits = 0;
  for(SIZE_T i = 0; i<32; ++i){
    uint32 flag = 1<<i;
    if(flag&flag){
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
  m_flagMask |= flag;
}

bool 
WorldState::hasCondicion(uint32 condicion)
{
  auto flag = getFlag(condicion);
  return flag & m_flagMask;
}

void 
WorldState::setCondicion(uint32 condicion, bool isTrue)
{
  auto flag = getFlag(condicion);
  if(isTrue){
    m_wordlStateFlags |= flag;
  }
  else{
    m_wordlStateFlags = (m_wordlStateFlags^flag)&(~flag);
  }
}

bool 
WorldState::getCondicion(uint32 condicion)
{
  auto flag = getFlag(condicion);
  return flag&m_wordlStateFlags;
}

uint32 
WorldState::getNumOfDiferences(const WorldState& other)
{
  uint32 diferences = ((other.m_wordlStateFlags^m_wordlStateFlags)&
                       (other.m_flagMask&m_flagMask))|
                      (other.m_flagMask^m_flagMask);

  return countBitsOn(diferences);
}

uint32
WorldState::getNumOfUnsatisfiedCondicion(const WorldState& other)
{
  uint32 unsatisfied = m_flagMask&(
                        ~other.m_flagMask|(
                          other.m_flagMask&(
                            m_wordlStateFlags^other.m_wordlStateFlags
                          )
                        )
                       );
  return countBitsOn(unsatisfied);
}

uint32 
WorldState::getFlag(uint32 userFlag)
{
  auto flagPos = find(m_flagMapping.begin(),m_flagMapping.end(),userFlag)-m_flagMapping.begin();
  return 1<<flagPos;
}

}

