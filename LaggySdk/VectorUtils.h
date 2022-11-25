#pragma once


namespace Sdk
{
  template <typename T>
  void mergeVectors(std::vector<T>& a_v1, const std::vector<T>& i_v2)
  {
    a_v1.insert(a_v1.begin(), i_v2.begin(), i_v2.end());
  }

} // ns Sdk
