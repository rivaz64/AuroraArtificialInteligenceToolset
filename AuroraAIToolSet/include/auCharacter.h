#pragma once
#include "auSituation.h"

namespace auToolSeetSDK
{

class AU_UTILITY_EXPORT Character :
    public Thing
{
public:

  Character() : 
    Thing(THING_TYPE::kCharacter,"",nullptr), m_atributes(m_defaultAtributes){}

  Character(const String& n, void* p) :
    Thing(THING_TYPE::kCharacter,n,p), m_atributes(m_defaultAtributes) {}

  static Map<String,float> m_defaultAtributes;

public:

  Map<String,float> m_atributes;

  Map<String,float> m_pasions;
};

}


