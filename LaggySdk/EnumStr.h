#pragma once

#include "MapUtils.h"


#define DECLARE_ENUM_STR(EnumType) class EnumType##Str \
{ \
public: \
  static std::string toString(const EnumType i_enum); \
   \
  static EnumType fromString(const std::string& i_str); \
};


#define DEFINE_ENUM_STR(EnumType, DirectMap) \
std::string EnumType##Str::toString(const EnumType i_enum) \
{ \
  return DirectMap.at(i_enum); \
} \
EnumType EnumType##Str::fromString(const std::string& i_str) \
{ \
  static std::unordered_map<std::string, EnumType> InverseMap = Sdk::inverseMap(DirectMap); \
  return InverseMap.at(i_str); \
}
