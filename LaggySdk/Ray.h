#pragma once

#include "Vector.h"


namespace Sdk
{
  template <typename T>
  class Ray
  {
  public:
    static Ray createFromTwoPoints(Vector3<T> i_point, Vector3<T> i_otherPoint)
    {
      return Ray(i_point, i_otherPoint - i_point);
    }
    static Ray createFromPointAndDir(Vector3<T> i_point, Vector3<T> i_dir)
    {
      return Ray(i_point, i_dir);
    }

  public:
    const Vector3<T>& getPoint() const { return d_point; }
    const Vector3<T>& getDir() const { return d_dir; }
    const Vector3<T>& getDirInv() const { return d_dirInv; }

    void translate(Vector3<T> i_translation)
    {
      d_point += i_translation;
    }

  private:
    Ray(Vector3<T> i_point, Vector3<T> i_dir)
      : d_point(i_point)
      , d_dir(i_dir)
    {
      updateDirs();
    }

    Vector3<T> d_point;
    Vector3<T> d_dir;
    Vector3<T> d_dirInv;

    void updateDirs()
    {
      d_dir.normalize();
      d_dirInv = d_dir;
      d_dirInv.inverse();
    }
  };


  using RayI = Ray<int>;
  using RayF = Ray<float>;
  using RayD = Ray<double>;

} // ns Sdk
