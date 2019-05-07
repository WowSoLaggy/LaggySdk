#pragma once


namespace Sdk
{
  const double Pi = 3.14159265358979323846;
  const double PiHalf = Pi / 2.0;

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

} // ns Sdk
