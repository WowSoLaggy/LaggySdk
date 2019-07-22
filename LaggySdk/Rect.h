#pragma once

#include "Vector.h"


namespace Sdk
{
  class Rect
  {
  public:
    Rect(float i_width, float i_height);

    float getWidth() const { return d_width; }
    float getHeight() const { return d_height; }

    float getWidthHalf() const { return d_widthHalf; }
    float getHeightHalf() const { return d_heightHalf; }

    void setWidth(float i_width);
    void setHeight(float i_height);

    bool containsPoint(const Vector2F& i_point) const;

  private:
    float d_width;
    float d_height;
    float d_widthHalf;
    float d_heightHalf;
  };

} // ns Sdk
