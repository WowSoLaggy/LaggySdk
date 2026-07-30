#pragma once

#include "Rect.h"
#include "Vector.h"


namespace Sdk
{
  // 2D analogue of an OBB: a local axis-aligned Rect placed by a translation and a rotation.
  template <typename T>
  class OrientedRect
  {
  public:
    OrientedRect() = default;

    OrientedRect(Rect<T> i_rect, Vector2<T> i_translation = {}, double i_rotation = 0.0)
      : d_rect(std::move(i_rect))
      , d_translation(std::move(i_translation))
      , d_rotation(i_rotation)
    {
    }

    const Rect<T>& getRect() const { return d_rect; }
    const Vector2<T>& getTranslation() const { return d_translation; }
    double getRotation() const { return d_rotation; }

    void setRect(Rect<T> i_rect) { d_rect = std::move(i_rect); }
    void setTranslation(Vector2<T> i_translation) { d_translation = std::move(i_translation); }
    void setRotation(const double i_rotation) { d_rotation = i_rotation; }

    // World-space centre of the box (translation plus the rotated local rect midpoint).
    Vector2<T> getCenter() const
    {
      Vector2<T> center = d_rect.center();
      center.rotate(d_rotation);
      return center + d_translation;
    }

    bool containsPoint(const Vector2<T>& i_point) const
    {
      Vector2<T> local = i_point - d_translation; // world -> local: undo translation then rotation
      local.rotate(-d_rotation);
      return d_rect.containsPoint(local);
    }

  private:
    Rect<T> d_rect;
    Vector2<T> d_translation;
    double d_rotation{ 0.0 };
  };


  using OrientedRectI = OrientedRect<int>;
  using OrientedRectF = OrientedRect<float>;
  using OrientedRectD = OrientedRect<double>;

} // ns Sdk
