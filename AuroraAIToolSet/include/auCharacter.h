#pragma once
#include "auSituation.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT Character :
    public Thing
{
public:

  Character() : 
    Thing(THING_TYPE::kCharacter,"",nullptr){}

  Character(const String& n, void* p) :
    Thing(THING_TYPE::kCharacter,n,p) {}

  float 
  getGeneralPasion(const String& pasion);

  float 
  getGeneralPerception(const String& name);

  float 
  getPasionFrom(const String& pasion, const String& name);

  void 
  setPasionTo(const String& pasion, const String& name, float change);

public:

  Map<String,Map<String,float>> m_pasions;
};

}


