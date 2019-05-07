#pragma once

#include "Vector.h"


namespace Sdk
{
  class Circle
  {
  public:

    Circle(float i_radius);
    virtual ~Circle() = default;

    float getRadius() const { return d_radius; }
    float getRadiusSq() const { return d_radiusSq; }

    void setRadius(float i_radius);

    bool containsPoint(const Vector2& i_point) const;

  private:
    float d_radius;
    float d_radiusSq;
  };

} // ns Sdk
