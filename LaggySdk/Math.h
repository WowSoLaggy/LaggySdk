#pragma once

#include "vector.h"

#include <cstdint>


namespace Sdk
{
  constexpr double Pi = 3.14159265358979323846;
  constexpr double PiHalf = Pi / 2.0;
  constexpr double Pi2 = Pi * 2;


  enum class Quadrant : std::int32_t
  {
    I = 1,
    II = 2,
    III = 3,
    IV = 4,
  };

  enum class Side : std::int32_t
  {
    Up = 0,
    Left = 1,
    Down = 2,
    Right = 3,
  };


  template <typename T>
  T getPi()
  {
    return (T)(Pi);
  }

  template <typename T>
  T degToRad(T i_val)
  {
    return i_val * getPi<T>() / 180;
  }


  template<typename T>
  Quadrant getQuadrant(const Vector2<T> i_v)
  {
    if (i_v.x * i_v.y > 0)
    {
      return i_v.x > 0 ? Quadrant::I : Quadrant::III;
    }
    else
    {
      return i_v.x > 0 ? Quadrant::IV : Quadrant::II;
    }
  }

  template<typename T>
  Side getSide(const Vector2<T> i_v)
  {
    if (i_v.x > i_v.y)
    {
      return -i_v.x > i_v.y ? Side::Down : Side::Right;
    }
    else
    {
      return -i_v.x > i_v.y ? Side::Left : Side::Up;
    }
  }

} // ns Sdk
