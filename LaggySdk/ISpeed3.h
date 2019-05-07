#pragma once

#include "Vector.h"


namespace Sdk
{
  class ISpeed3
  {
  public:
    ISpeed3() : d_speed(Vector3::zero()) { }
    virtual ~ISpeed3() = default;

    Vector3 getSpeed() const { return d_speed; }
    void setSpeed(Vector3 i_speed) { d_speed = std::move(i_speed); }

  private:
    Vector3 d_speed;
  };

} // ns Sdk
