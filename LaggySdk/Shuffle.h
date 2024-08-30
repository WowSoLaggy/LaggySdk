#pragma once


namespace Sdk
{
  template <typename T>
  void shuffleVector(std::vector<T>& io_vector)
  {
    std::shuffle(io_vector.begin(), io_vector.end(), std::mt19937(std::random_device()()));
  }

} // ns Sdk
