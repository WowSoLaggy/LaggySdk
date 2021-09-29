#pragma once

#include "Vector.h"


namespace Sdk
{
  template <typename T>
  class Circle
  {
  public:
    Circle(const T i_radius, const Vector2<T> i_center = Vector2<T>::zero())
    {
      setCenter(std::move(i_center));
      setRadius(std::move(i_radius));
    }

    virtual ~Circle() = default;

    T getRadius() const { return d_radius; }
    T getRadiusSq() const { return d_radiusSq; }

    const Vector2<T>& getCenter() const { return d_center; }
    void setCenter(const Vector2<T> i_center) { d_center = std::move(i_center); }

    void setRadius(const T i_radius)
    {
      d_radius = std::move(i_radius);
      d_radiusSq = d_radius * d_radius;
    }

    bool containsPoint(const Vector2<T>& i_point) const
    {
      return i_point.lengthSq() <= d_radiusSq;
    }

  private:
    T d_radius;
    T d_radiusSq;

    Vector2<T> d_center;
  };


  using CircleI = Circle<int>;
  using CircleF = Circle<float>;
  using CircleD = Circle<double>;

} // ns Sdk
