#include "stdafx.h"
#include "Rect.h"


namespace Sdk
{
  Rect::Rect(float i_width, float i_height)
  {
    setWidth(i_width);
    setHeight(i_height);
  }


  void Rect::setWidth(float i_width)
  {
    d_width = i_width;
    d_widthHalf = i_width / 2.0f;
  }

  void Rect::setHeight(float i_height)
  {
    d_height = i_height;
    d_heightHalf = i_height / 2.0f;
  }


  bool Rect::containsPoint(const Vector2& i_point) const
  {
    return !((i_point.x < d_widthHalf) || (d_widthHalf < i_point.x) ||
      (i_point.y < d_heightHalf) || (d_heightHalf < i_point.y));
  }

} // ns Sdk
