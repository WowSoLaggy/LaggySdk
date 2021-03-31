#include "stdafx.h"
#include "Shapes.h"

#include "Math.h"


namespace Sdk
{
  std::vector<Vector2F> getPointsOnCircle(const float i_radius, const int i_numPoints)
  {
    std::vector<Vector2F> points(i_numPoints);

    const double angleDiff = Pi2 / i_numPoints;

    Vector2F point{ 0.0f, -i_radius };
    points[0] = point;
    for (int i = 1; i < i_numPoints; ++i)
    {
      point.rotate(angleDiff, { 0, 0 });
      points[i] = point;
    }

    return points;
  }

} // ms Sdk
