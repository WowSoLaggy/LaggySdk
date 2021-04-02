#pragma once

#include "Streams.h"

#include <iostream>
#include <string>


namespace Sdk
{
  template <typename T>
  struct Vector2
  {
    T x{ (T)0 };
    T y{ (T)0 };

    static Vector2 zero() { return { (T)0, (T)0 }; }
    static Vector2 identity() { return { (T)1, (T)1 }; }

    T lengthSq() const { return x * x + y * y; }
    T length() const { return std::sqrt(lengthSq()); }

    void normalize()
    {
      T l = length();
      x /= l;
      y /= l;
    }

    bool operator==(const Vector2<T>& i_right) const { return x == i_right.x && y == i_right.y; }
    bool operator!=(const Vector2<T>& i_right) const { return !operator==(i_right); }

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
    T det(const Vector2<T>& i_v) const { return x * i_v.y - y * i_v.x; }

    double angle(const Vector2<T>& i_v) const
    {
      const double dotValue = dot(i_v);
      const double detValue = det(i_v);
      return std::atan2(detValue, dotValue);
    }


    void rotate(double i_angle, Vector2<T> i_origin)
    {
      T x1 = x - i_origin.x;
      T y1 = y - i_origin.y;

      const double cos = std::cos(i_angle);
      const double sin = std::sin(i_angle);

      x = static_cast<T>(x1 * cos - y1 * sin);
      y = static_cast<T>(x1 * sin + y1 * cos);

      x = x + i_origin.x;
      y = y + i_origin.y;
    }

    
    friend std::ostream& operator<<(std::ostream& io_stream, const Vector2<T>& i_vector)
    {
      write(io_stream, i_vector.x);
      write(io_stream, i_vector.y);

      return io_stream;
    }

    friend std::istream& operator>>(std::istream& io_stream, Vector2<T>& o_vector)
    {
      read(io_stream, o_vector.x);
      read(io_stream, o_vector.y);

      return io_stream;
    }
  };

  struct Vector2_hash {
  public:
    template <typename T>
    std::size_t operator()(const Vector2<T>& i_v) const
    {
      return std::hash<T>()(i_v.x) ^ std::hash<T>()(i_v.y);
    }
  };


  template <typename T>
  struct Vector3
  {
    T x{ (T)0 };
    T y{ (T)0 };
    T z{ (T)0 };

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

    bool operator==(const Vector3<T>& i_right) const { return x == i_right.x && y == i_right.y && z == i_right.z; }
    bool operator!=(const Vector3<T>& i_right) const { return !operator==(i_right); }

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


    friend std::ostream& operator<<(std::ostream& io_stream, const Vector3<T>& i_vector)
    {
      write(io_stream, i_vector.x);
      write(io_stream, i_vector.y);
      write(io_stream, i_vector.z);

      return io_stream;
    }

    friend std::istream& operator>>(std::istream& io_stream, Vector3<T>& o_vector)
    {
      read(io_stream, o_vector.x);
      read(io_stream, o_vector.y);
      read(io_stream, o_vector.z);

      return io_stream;
    }
  };


  template <typename T>
  struct Vector4
  {
    T x{ (T)0 };
    T y{ (T)0 };
    T z{ (T)0 };
    T w{ (T)0 };

    static Vector4 zero() { return { (T)0, (T)0, (T)0, (T)0 }; }
    static Vector4 identity() { return { (T)1, (T)1, (T)1, (T)1 }; }

    T lengthSq() const { return x * x + y * y + z * z + w * w; }
    T length() const { return std::sqrt<T>(lengthSq()); }

    void normalize()
    {
      T length = length();
      x /= length;
      y /= length;
      z /= length;
      w /= length;
    }

    bool operator==(const Vector4<T>& i_right) const { return
      x == i_right.x && y == i_right.y &&
      z == i_right.z && w == i_right.w; }
    bool operator!=(const Vector4<T>& i_right) const { return !operator==(i_right); }

    void operator+=(const Vector4<T>& i_right)
    {
      x += i_right.x;
      y += i_right.y;
      z += i_right.z;
      w += i_right.w;
    }
    void operator-=(const Vector2<T>& i_right) { operator+=(-i_right); }
    
    Vector4<T> operator-() const { return Vector4<T>{ -x, -y, -z, -w }; }
    Vector4<T> operator+(const Vector4<T>& i_right) const { return Vector4<T>{ x + i_right.x, y + i_right.y,
      z + i_right.z, w + i_right.w }; }
    Vector4<T> operator-(const Vector4<T>& i_right) const { return operator+(-i_right); }
    Vector4<T> operator*(T i_right) const { return Vector4<T>{ x * i_right, y * i_right, z * i_right, w * i_right }; }
    Vector4<T> operator/(T i_right) const { return Vector4<T>{ x / i_right, y / i_right, z / i_right, w / i_right }; }


    friend std::ostream& operator<<(std::ostream& io_stream, const Vector4<T>& i_vector)
    {
      write(io_stream, i_vector.x);
      write(io_stream, i_vector.y);
      write(io_stream, i_vector.z);
      write(io_stream, i_vector.w);

      return io_stream;
    }

    friend std::istream& operator>>(std::istream& io_stream, Vector4<T>& o_vector)
    {
      read(io_stream, o_vector.x);
      read(io_stream, o_vector.y);
      read(io_stream, o_vector.z);
      read(io_stream, o_vector.w);

      return io_stream;
    }
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
