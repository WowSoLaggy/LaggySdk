#pragma once

#include "Math.h"
#include "Polyline.h"
#include "Vector.h"


namespace Sdk
{
  // A Catmull-Rom spline through a list of 2D control points.
  //
  // Catmull-Rom passes through every control point and is C1-continuous: you place
  // waypoints and the curve threads them. The spline is purely 2D.
  //
  // A "segment" is the curve between control point i and i+1; there are
  // (count - 1) segments. The endpoints reuse the first/last control point as the
  // phantom neighbours so the curve still reaches the ends.
  template <typename T>
  class Spline
  {
  public:
    explicit Spline(Polyline2<T> i_controlPoints)
      : d_controlPoints(std::move(i_controlPoints))
    {
    }

    int getSegmentsCount() const
    {
      const auto count = d_controlPoints.points.size();
      return count < 2 ? 0 : (int)count - 1;
    }

    bool isEmpty() const
    {
      return getSegmentsCount() == 0;
    }

    // Point / tangent on segment i_seg at local i_t in [0, 1]. i_t == 0 lands on
    // control point i_seg, i_t == 1 on control point i_seg + 1.
    Vector2<T> pointAt(const int i_seg, const T i_t) const
    {
      Vector2<T> p0, p1, p2, p3;
      getSegmentPoints(i_seg, p0, p1, p2, p3);
      return catmullRom(p0, p1, p2, p3, i_t);
    }

    Vector2<T> tangentAt(const int i_seg, const T i_t) const
    {
      Vector2<T> p0, p1, p2, p3;
      getSegmentPoints(i_seg, p0, p1, p2, p3);
      Vector2<T> tangent = catmullRomTangent(p0, p1, p2, p3, i_t);
      if (tangent.isNotZero((T)1e-5))
        tangent.normalize();
      return tangent;
    }

    // Walks the whole spline emitting samples roughly every i_stepLen world units.
    // The polyline endpoints coincide with the first/last control point.
    Polyline2<T> sampleByStep(const T i_stepLen) const
    {
      std::vector<Vector2<T>> samples;
      if (isEmpty())
        return samples;

      CONTRACT_EXPECT(i_stepLen > (T)0);

      const int segs = getSegmentsCount();
      for (int seg = 0; seg < segs; ++seg)
      {
        // Approximate the segment's length to pick a subdivision count, so the
        // sample spacing stays close to i_stepLen regardless of segment size.
        const T chord = (pointAt(seg, (T)1) - pointAt(seg, (T)0)).length();
        const int steps = std::max(1, (int)std::ceil(chord / i_stepLen));

        // Emit the segment start once (the first segment), then every step end. This
        // keeps the joins between segments from duplicating a sample.
        if (seg == 0)
          samples.push_back(pointAt(seg, (T)0));

        for (int s = 1; s <= steps; ++s)
          samples.push_back(pointAt(seg, (T)s / steps));
      }

      return samples;
    }

    const Polyline2<T>& getControlPoints() const
    {
      return d_controlPoints;
    }

  private:
    Polyline2<T> d_controlPoints;

    // Returns the four control points (with clamped phantom ends) governing i_seg.
    void getSegmentPoints(
      const int i_seg, Vector2<T>& o_p0, Vector2<T>& o_p1,
      Vector2<T>& o_p2, Vector2<T>& o_p3) const
    {
      CONTRACT_EXPECT(i_seg >= 0 && i_seg < getSegmentsCount());

      const std::vector<Vector2<T>>& pts = d_controlPoints.points;
      const int last = (int)pts.size() - 1;
      const int i0 = clamp(i_seg - 1, 0, last);
      const int i1 = i_seg;
      const int i2 = i_seg + 1;
      const int i3 = clamp(i_seg + 2, 0, last);

      o_p0 = pts[i0];
      o_p1 = pts[i1];
      o_p2 = pts[i2];
      o_p3 = pts[i3];
    }

    // Catmull-Rom basis at local parameter i_t over its four control points.
    static Vector2<T> catmullRom(
      const Vector2<T>& i_p0, const Vector2<T>& i_p1,
      const Vector2<T>& i_p2, const Vector2<T>& i_p3, const T i_t)
    {
      const T t = i_t;
      const T t2 = t * t;
      const T t3 = t2 * t;

      return (i_p1 * (T)2
        + (i_p2 - i_p0) * t
        + (i_p0 * (T)2 - i_p1 * (T)5 + i_p2 * (T)4 - i_p3) * t2
        + (i_p1 * (T)3 - i_p0 - i_p2 * (T)3 + i_p3) * t3) * (T)0.5;
    }

    // Derivative of the Catmull-Rom basis w.r.t. t (the unnormalized tangent).
    static Vector2<T> catmullRomTangent(
      const Vector2<T>& i_p0, const Vector2<T>& i_p1,
      const Vector2<T>& i_p2, const Vector2<T>& i_p3, const T i_t)
    {
      const T t = i_t;
      const T t2 = t * t;

      return ((i_p2 - i_p0)
        + (i_p0 * (T)2 - i_p1 * (T)5 + i_p2 * (T)4 - i_p3) * ((T)2 * t)
        + (i_p1 * (T)3 - i_p0 - i_p2 * (T)3 + i_p3) * ((T)3 * t2)) * (T)0.5;
    }
  };


  using SplineI = Spline<int>;
  using SplineF = Spline<float>;
  using SplineD = Spline<double>;

} // ns Sdk
