#pragma once

#include "RandomGenerator.h"


namespace Sdk
{
  // Sets current time as a seed of the randomizer
  void randomize();

  // Returns a random integer in the range [i_left, i_right]
  template <typename T>
  T randomInt(const T i_left, const T i_right)
  {
    UniformIntGenerator<T> generator(i_left, i_right);
    return generator.getNextValue();
  }


  template <typename T>
  T randomReal(const T i_left, const T i_right)
  {
    UniformRealGenerator<T> generator(i_left, i_right);
    return generator.getNextValue();
  }

} // ns Sdk
