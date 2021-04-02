#pragma once

#include "Vector.h"


namespace Sdk
{
  std::vector<Vector2F> getPointsOnCircle(float i_radius, int i_numPoints);
  std::vector<Vector2F> getPointsOnCircle(float i_radius, int i_numPoints,
                                          float i_startAngle, float i_endAngle);

} // ms Sdk
