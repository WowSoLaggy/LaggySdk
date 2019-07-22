#pragma once

#include <string>


namespace Sdk
{
  template <typename T>
  struct Vector2
  {
    T x;
    T y;

    static Vector2 zero() { return { (T)0, (T)0 }; }
    static Vector2 identity() { return { (T)1, (T)1 }; }

    T lengthSq() const { return x * x + y * y; }
    T length() const { return std::sqrt<T>(lengthSq); }

    void normalize()
    {
      T length = length();
      x /= length;
      y /= length;
    }

    void operator+=(const Vector2<T>& i_right)
    {
      x += i_right.x;
      y += i_right.y;
    }
    void operator-=(const Vector2<T>& i_right) { operator+=(-i_right); }

    Vector2<T> operator-() const { return Vector2<T>{ -x, -y }; }
    Vector2<T> operator+(const Vector2<T>& i_right) const { return Vector2<T>{ x + i_right.x, y + i_right.y }; }
    Vector2<T> operator-(const Vector2<T>& i_right) const {
      return operator+(-i_right);
    }
    Vector2<T> operator*(T i_right) const { return Vector2<T>{ x * i_right, y * i_right }; }
    Vector2<T> operator/(T i_right) const { return Vector2<T>{ x / i_right, y / i_right }; }

    T dot(const Vector2<T>& i_v) const { return x * i_v.x + y * i_v.y; }
  };

  template <typename T>
  struct Vector3
  {
    T x;
    T y;
    T z;

    static Vector3 zero() { return { (T)0, (T)0, (T)0 }; }
    static Vector3 identity() { return { (T)1, (T)1, (T)1 }; }

    T lengthSq() const { return x * x + y * y + z * z; }
    T length() const { return std::sqrt(lengthSq()); }

    void normalize()
    {
      T l = length();
      x /= l;
      y /= l;
      z /= l;
    }

    void operator+=(const Vector3<T>& i_right)
    {
      x += i_right.x;
      y += i_right.y;
      z += i_right.z;
    }
    void operator-=(const Vector2<T>& i_right) { operator+=(-i_right); }

    Vector3<T> operator-() const { return Vector3<T>{ -x, -y, -z }; }
    Vector3<T> operator+(const Vector3<T>& i_right) const { return Vector3<T>{ x + i_right.x, y + i_right.y,
      z + i_right.z }; }
    Vector3<T> operator-(const Vector3<T>& i_right) const { return operator+(-i_right); }
    Vector3<T> operator*(T i_right) const { return Vector3<T>{ x * i_right, y * i_right, z * i_right }; }
    Vector3<T> operator/(T i_right) const { return Vector3<T>{ x / i_right, y / i_right, z / i_right }; }

    Vector3<T> cross(const Vector3<T>& i_v) const
    {
      return {
        y * i_v.z - z * i_v.y,
        z * i_v.x - x * i_v.z,
        x * i_v.y - y * i_v.x
      };
    }
  };
  
  template <typename T>
  struct Vector4
  {
    T x;
    T y;
    T z;
    T w;

    static Vector4 zero() { return { (T)0, (T)0, (T)0, (T)0 }; }
    static Vector4 identity() { return { (T)1, (T)1, (T)1, (T)1 }; }

    T lengthSq() const { return x * x + y * y + z * z + w * w; }
    T length() const { return std::sqrt<T>(lengthSq); }

    void normalize()
    {
      T length = length();
      x /= length;
      y /= length;
      z /= length;
      w /= length;
    }

    void operator+=(const Vector4<T>& i_right)
    {
      x += i_right.x;
      y += i_right.y;
      z += i_right.z;
      w += i_right.w;
    }
    void operator-=(const Vector2<T>& i_right) { operator+=(-i_right); }
    
    Vector4<T> operator-() const { return Vector4<T>{ -x, -y, -z, -w }; }
    Vector4<T> operator+(const Vector4<T>& i_right) { return Vector4<T>{ x + i_right.x, y + i_right.y,
      z + i_right.z, w + i_right.w }; }
    Vector4<T> operator-(const Vector4<T>& i_right) { return operator+(-i_right); }
    Vector4<T> operator*(T i_right) { return Vector4<T>{ x * i_right, y * i_right, z * i_right, w * i_right }; }
    Vector4<T> operator/(T i_right) { return Vector4<T>{ x / i_right, y / i_right, z / i_right, w / i_right }; }
  };

  using Vector2I = Vector2<int>;
  using Vector3I = Vector3<int>;
  using Vector4I = Vector4<int>;
  using Vector2F = Vector2<float>;
  using Vector3F = Vector3<float>;
  using Vector4F = Vector4<float>;
  using Vector2D = Vector2<double>;
  using Vector3D = Vector3<double>;
  using Vector4D = Vector4<double>;
} // ns Sdk
