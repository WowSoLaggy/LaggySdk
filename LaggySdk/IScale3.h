#pragma once

#include "Vector.h"


namespace Sdk
{
  class IScale3
  {
  public:
    IScale3() : d_scale(Vector3::identity()) { }
    virtual ~IScale3() = default;

    Vector3 getScale() const { return d_scale; }
    void setScale(Vector3 i_scale) { d_scale = std::move(i_scale); }

  private:
    Vector3 d_scale;
  };

} // ns Sdk
