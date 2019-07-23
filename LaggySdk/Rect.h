#pragma once

#include "Vector.h"

#include <algorithm>


namespace Sdk
{
  template <typename T>
  struct Rect
  {
    Rect()
      : Rect((T)0, (T)0, (T)0, (T)0)
    {
    }

    Rect(Vector2<T> i_p1, Vector2<T> i_p2)
      : p1(std::move(i_p1))
      , p2(std::move(i_p2))
    {
    }

    Rect(T left, T right, T top, T bottom)
      : p1({ left, top })
      , p2({ right, bottom })
    {
    }

    Vector2<T> p1;
    Vector2<T> p2;

    T left() const { return std::min<T>(p1.x, p2.x); }
    T right() const { return std::max<T>(p1.x, p2.x); }
    T top() const { return std::min<T>(p1.y, p2.y); }
    T bottom() const { return std::max<T>(p1.y, p2.y); }

    T width() const { return right() - left(); }
    T height() const { return bottom() - top(); }

    T width2() const { return (right() - left()) / 2; }
    T height2() const { return (bottom() - top()) / 2; }

    Vector2<T> center() const { return (p1 + p2) / 2; }
    Vector2<T> topLeft() const { return { left(), top() }; }
    Vector2<T> bottomRight() const { return { right(), bottom() }; }


    bool containsPoint(const Vector2<T>& i_point) const
    {
      return left() <= i_point.x && i_point.x <= right() && top() <= i_point.y && i_point.y <= bottom();
    }

    bool intersectRect(const Rect<T>& i_rect) const
    {
      return !(i_rect.left() > right() || i_rect.right() < left() || i_rect.top() > bottom() || i_rect.bottom() < top());
    }
  };

  using RectI = Rect<int>;
  using RectF = Rect<float>;
  using RectD = Rect<double>;

} // ns Sdk
