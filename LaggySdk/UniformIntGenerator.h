#pragma once

namespace Sdk
{
  // Generates uniformly-distributed int in closed interval [i_left, i_right]
  template<typename T>
  class UniformIntGenerator
  {
  public:
    UniformIntGenerator(const T i_left, const T i_right)
      : d_randomEngine(d_randomDevice())
      , d_distribution(i_left, i_right)
    {
    }

    T getNextValue()
    {
      return d_distribution(d_randomEngine);
    }

  private:
    std::random_device d_randomDevice;
    std::mt19937 d_randomEngine;
    std::uniform_int_distribution<T> d_distribution;
  };

} // ns Sdk
