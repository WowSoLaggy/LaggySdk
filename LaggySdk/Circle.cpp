#include "stdafx.h"
#include "Circle.h"


namespace Sdk
{
  Circle::Circle(float i_radius)
  {
    setRadius(i_radius);
  }


  void Circle::setRadius(float i_radius)
  {
    d_radius = i_radius;
    d_radiusSq = i_radius * i_radius;
  }


  bool Circle::containsPoint(const Vector2F& i_point) const
  {
    return i_point.lengthSq() <= d_radiusSq;
  }

} // ns Sdk
