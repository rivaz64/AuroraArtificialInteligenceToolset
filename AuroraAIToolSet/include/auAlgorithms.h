#pragma once
#include "auPrerequisites.h"

namespace auToolSeetSDK
{

template<class T>
bool
contains(const Vector<T>& v, const T& val){
  return find(v.begin(),v.end(),val) != v.end();
}

template<class T>
T
getRandom(const Vector<T>& v)
{
  return v[rand()%v.size()];
}

//template<class T>
//void
//erase(const Vector<T>& v, const T& val){
//  auto pos = find(v.begin(),v.end(),val);
//  v.erase(pos);
//}

template<class T>
Vector<T>
intersection(const Vector<T>& v1, const Vector<T>& v2)
{
  Vector<T> ans;
  for(auto& v : v1){
    if(contains(v2,v)){
      ans.push_back(v);
    }
  }
  return ans;
}

template<class T>
Vector<T>
notIntersection(const Vector<T>& v1, const Vector<T>& v2)
{
  Vector<T> ans;
  for(auto& v : v1){
    if(!contains(v2,v)){
      ans.push_back(v);
    }
  }
  for(auto& v : v2){
    if(!contains(v1,v)){
      ans.push_back(v);
    }
  }
  return ans;
}

}
