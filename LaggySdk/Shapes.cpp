#include "stdafx.h"
#include "Shapes.h"

#include "Math.h"


namespace Sdk
{
  std::vector<Vector2F> getPointsOnCircle(const float i_radius, const int i_numPoints)
  {
    std::vector<Vector2F> points(i_numPoints, { 0.0f, -i_radius });

    const double angleDiff = Pi2 / i_numPoints;
    for (int i = 0; i < i_numPoints; ++i)
      points[i].rotate(angleDiff * i, { 0, 0 });

    return points;
  }

  std::vector<Vector2F> getPointsOnCircle(const float i_radius, const int i_numPoints,
                                          const float i_startAngle, const float i_endAngle)
  {
    std::vector<Vector2F> points(i_numPoints, { 0.0f, -i_radius });

    const double angleDiff = (i_endAngle - i_startAngle) / (i_numPoints - 1);
    for (int i = 0; i < i_numPoints; ++i)
      points[i].rotate(i_startAngle + angleDiff * i, { 0, 0 });

    return points;
  }

} // ns Sdk
