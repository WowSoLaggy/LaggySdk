#pragma once

#include "Vector.h"


namespace Sdk
{
  template <typename T>
  class Segment2
  {
  public:
    Segment2() = default;

    Segment2(Vector2<T> i_start, Vector2<T> i_end)
      : start(std::move(i_start))
      , end(std::move(i_end))
    {
    }

    Vector2<T> start;
    Vector2<T> end;

    Vector2<T> getDir() const { return end - start; }

    T getLength() const { return getDir().length(); }
    T getLengthSq() const { return getDir().lengthSq(); }

    Vector2<T> getMidpoint() const { return (start + end) / static_cast<T>(2); }

    // `i_t` is the distance along the segment from start (0) to end (length). Can be negative or beyond length.
    Vector2<T> pointAt(const T i_t) const { return start + getDir() * i_t; }

    void translate(const Vector2<T>& i_translation)
    {
      start += i_translation;
      end += i_translation;
    }

    // Closest point on this segment to i_p (clamped to the endpoints).
    Vector2<T> closestPointTo(const Vector2<T>& i_p) const
    {
      const Vector2<T> dir = getDir();
      const T lenSq = dir.lengthSq();
      if (lenSq <= static_cast<T>(0))
        return start;
      const T t = clamp((i_p - start).dot(dir) / lenSq, static_cast<T>(0), static_cast<T>(1));
      return start + dir * t;
    }

    // Intersection point with another segment, or nullopt if they don't cross
    // (parallel/collinear segments never report a hit).
    std::optional<Vector2<T>> intersect(const Segment2<T>& i_other) const
    {
      const Vector2<T> r = getDir();
      const Vector2<T> s = i_other.getDir();
      const T denom = r.det(s);
      if (std::abs(denom) < static_cast<T>(1e-9))
        return std::nullopt;  // parallel / collinear

      const Vector2<T> qp = i_other.start - start;
      const T t = qp.det(s) / denom;
      const T u = qp.det(r) / denom;
      if (t < static_cast<T>(0) || t > static_cast<T>(1) ||
          u < static_cast<T>(0) || u > static_cast<T>(1))
        return std::nullopt;

      return start + r * t;
    }
  };


  template <typename T>
  class Segment3
  {
  public:
    Segment3() = default;

    Segment3(Vector3<T> i_start, Vector3<T> i_end)
      : start(std::move(i_start))
      , end(std::move(i_end))
    {
    }

    Vector3<T> start;
    Vector3<T> end;

    Vector3<T> getDir() const { return end - start; }

    T getLength() const { return getDir().length(); }
    T getLengthSq() const { return getDir().lengthSq(); }

    Vector3<T> getMidpoint() const { return (start + end) / static_cast<T>(2); }

    // `i_t` is the distance along the segment from start (0) to end (length). Can be negative or beyond length.
    Vector3<T> pointAt(const T i_t) const { return start + getDir() * i_t; }

    void translate(const Vector3<T>& i_translation)
    {
      start += i_translation;
      end += i_translation;
    }
  };


  using Segment2I = Segment2<int>;
  using Segment2F = Segment2<float>;
  using Segment2D = Segment2<double>;

  using Segment3I = Segment3<int>;
  using Segment3F = Segment3<float>;
  using Segment3D = Segment3<double>;

} // ns Sdk
