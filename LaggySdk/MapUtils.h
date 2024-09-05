#pragma once

#include <unordered_map>


namespace Sdk
{
  template <typename T, typename U>
  std::unordered_map<U, T> inverseMap(const std::unordered_map<T, U>& i_map)
  {
    std::unordered_map<U, T> res;
    for (const auto& [first, second] : i_map)
      res.insert({ second, first });
    return res;
  }


  template <typename MapType>
  auto keys(const MapType& myMap)
  {
    std::vector<typename MapType::key_type> keyList;
    for (const auto& pair : myMap)
      keyList.push_back(pair.first);
    return keyList;
  }

} // ns Sdk
