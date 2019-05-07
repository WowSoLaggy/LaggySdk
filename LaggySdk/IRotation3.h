#pragma once

#include "Vector.h"


namespace Sdk
{
  class IRotation3
  {
  public:
    IRotation3() : d_rotation(Vector3::zero()) { }
    virtual ~IRotation3() = default;

    Vector3 getRotation() const { return d_rotation; }

    void setRotation(Vector3 i_rotation) { d_rotation = std::move(i_rotation); }
    void setRotationX(float i_x) { d_rotation.x = i_x; }
    void setRotationY(float i_y) { d_rotation.y = i_y; }
    void setRotationZ(float i_z) { d_rotation.z = i_z; }

  private:
    Vector3 d_rotation;
  };

} // ns Sdk
