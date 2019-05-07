#pragma once

#include "Vector.h"


namespace Sdk
{
  class IPosition3
  {
  public:
    IPosition3() : d_position(Vector3::zero()) { }
    virtual ~IPosition3() = default;

    Vector3 getPosition() const { return d_position; }
    void setPosition(Vector3 i_position) { d_position = std::move(i_position); }

  private:
    Vector3 d_position;
  };

} // ns Sdk
