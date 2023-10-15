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

} // ns Sdk
