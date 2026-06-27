#pragma once

#include "Segment.h"
#include "Vector.h"


namespace Sdk
{
  // A crossing of one polyline by another: the segment of the queried polyline it
  // lies on (segment [seg-1, seg], so seg is in [1, points.size()-1]) and the point.
  template <typename T>
  struct Polyline2Crossing
  {
    size_t seg = 0;        // index of the queried polyline's segment carrying the crossing
    Vector2<T> point;      // intersection point
  };


  // An ordered chain of 2D points.
  template <typename T>
  struct Polyline2
  {
    std::vector<Vector2<T>> points;

    Polyline2() = default;
    Polyline2(std::vector<Vector2<T>> i_points) : points(std::move(i_points)) {}

    // Read-only conveniences forwarding to the underlying point vector, so callers
    // index/iterate the polyline directly without reaching through `points`. Only
    // appending mutators (push_back/reserve) are exposed — appending keeps it a valid
    // chain; resize/erase/conversion-to-vector are deliberately omitted so this stays
    // a named type, not a vector in disguise.
    size_t size() const { return points.size(); }
    bool isEmpty() const { return points.size() < 2; }
    const Vector2<T>& operator[](const size_t i_i) const { return points[i_i]; }
    const Vector2<T>& front() const { return points.front(); }
    const Vector2<T>& back() const { return points.back(); }
    auto begin() const { return points.begin(); }
    auto end() const { return points.end(); }

    void push_back(const Vector2<T>& i_p) { points.push_back(i_p); }
    void reserve(const size_t i_n) { points.reserve(i_n); }

    // Every point where this polyline crosses i_other, ordered along this one (by
    // distance from points.front()). A polyline with fewer than two points has no
    // segments and yields nothing. Parallel/collinear overlaps never report a hit
    // (see Segment2::intersect).
    std::vector<Polyline2Crossing<T>> findCrossings(const Polyline2<T>& i_other) const
    {
      std::vector<Polyline2Crossing<T>> crossings;
      if (isEmpty() || i_other.isEmpty())
        return crossings;

      for (size_t i = 1; i < size(); ++i)
      {
        const Segment2<T> seg((*this)[i - 1], (*this)[i]);
        for (size_t j = 1; j < i_other.size(); ++j)
        {
          const auto x = seg.intersect(Segment2<T>(i_other[j - 1], i_other[j]));
          if (x)
            crossings.push_back({ i, *x });
        }
      }

      const Vector2<T>& origin = front();
      std::sort(crossings.begin(), crossings.end(),
        [&origin](const Polyline2Crossing<T>& i_l, const Polyline2Crossing<T>& i_r)
        { return (i_l.point - origin).lengthSq() < (i_r.point - origin).lengthSq(); });

      return crossings;
    }
  };


  using Polyline2F = Polyline2<float>;
  using Polyline2D = Polyline2<double>;

  using Polyline2CrossingF = Polyline2Crossing<float>;
  using Polyline2CrossingD = Polyline2Crossing<double>;

} // ns Sdk
