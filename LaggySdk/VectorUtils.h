#pragma once


namespace Sdk
{
  template <typename T>
  void mergeVectors(std::vector<T>& a_v1, const std::vector<T>& i_v2)
  {
    a_v1.insert(a_v1.begin(), i_v2.begin(), i_v2.end());
  }

  template <typename T>
  std::vector<T> mergeVectors(const std::vector<T>& i_v1, const std::vector<T>& i_v2)
  {
    std::vector<T> res;
    res.reserve(i_v1.size() + i_v2.size());
    res.insert(res.end(), i_v1.begin(), i_v1.end());
    res.insert(res.end(), i_v2.begin(), i_v2.end());
    return res;
  }

  template <typename T>
  std::set<T> mergeVectorsToSet(const std::vector<T>& i_v1, const std::vector<T>& i_v2)
  {
    std::set<T> res;
    res.insert(i_v1.begin(), i_v1.end());
    res.insert(i_v2.begin(), i_v2.end());
    return res;
  }

} // ns Sdk
