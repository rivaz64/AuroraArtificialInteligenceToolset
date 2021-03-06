/**
 * @file auSTDHeaders.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once

#pragma once

#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>
#include <fstream>
#include <functional>
#include "auDefines.h"

namespace auToolSeetSDK {

using std::vector;
using std::list;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::map;
using std::pair;
using std::enable_shared_from_this;
using std::istream_iterator;
using std::istringstream;
using std::string;
using std::wstring;
using std::fstream;
using std::ios;
using std::make_shared;
using std::reinterpret_pointer_cast;
using std::endl;
using std::copy;
using std::cout;
using std::to_string;
using std::find;
using std::function;


/**
 * @brief wraper of the std::vector, can be changed in the future
 * @tparam T
*/
template <typename T>
using Vector = vector<T>;

/**
 * @brief wraper of the std::list, can be changed in the future
 * @tparam T
*/
template <typename T>
using List = list<T>;

/**
 * @brief wraper of the std::list, can be changed in the future
 * @tparam T
*/
template <typename T>
using Set = set<T>;

/**
 * @brief wraper of the std::string, can be changed in the future
 * @tparam T
*/
using String = string;

/**
 * @brief wraper of the std::wstring, can be changed in the future
 * @tparam T
*/
using WString = wstring;

/**
 * @brief wraper of the std stream
*/
using FStream = fstream;

/**
 * @brief wraper of the std::shared_ptr, can be changed in the future
 * @tparam T
*/
template <typename T>
using SPtr = shared_ptr<T>;

/**
 * @brief wraper of the std::shared_ptr, can be changed in the future
 * @tparam T
*/
template <typename T>
using WPtr = weak_ptr<T>;

/**
 * @brief wraper of the std::swap
 * @tparam T
 * @param a
 * @param b
*/
FORCEINLINE void 
swap(float& a, float& b) {
  std::swap(a, b);
}

/**
 * @brief wraper for the std::map
 * @tparam T1 
 * @tparam T2 
*/
template <typename T1, typename T2>
using Map = map<T1,T2>;

/**
 * @brief wraper of the std::pair
 * @tparam T1 
 * @tparam T2 
*/
template <typename T1, typename T2>
using Pair = pair<T1,T2>;

/**
 * @brief cast for smart pointers
 * @tparam T 
 * @tparam U 
 * @param pointer 
 * @return 
*/
template<typename T,typename U>
FORCEINLINE SPtr<T> 
cast(const SPtr<U>& pointer){
  return reinterpret_pointer_cast<T>(pointer);
}

template<typename T>
FORCEINLINE SPtr<T> 
copy(const SPtr<T>& pointer){
  return make_shared<T>(*pointer.get());
}

/**
 * @brief wraper for a class that can make a shared from this
*/
template<typename T>
using SharedEnabled = enable_shared_from_this<T>;

template <typename T>
using Function = function<T>;

/**
 * @brief prints a string to the console
 * @param s 
*/
FORCEINLINE void
print(String s){
  cout<<s<<endl;
}

/**
* @brief wraper of the std::make_shared
* @tparam T
*/
template <typename T, typename... _Types>
FORCEINLINE SPtr<T> 
makeSPtr(_Types&&... _Args) {
  return make_shared<T>(std::forward<_Types>(_Args)...);
}

}