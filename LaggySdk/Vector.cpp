#include "stdafx.h"
#include "Vector.h"


namespace Sdk
{

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Vector2
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector2 operator+(const Vector2& i_left, const Vector2& i_right)
  {
    return { i_left.x + i_right.x, i_left.y + i_right.y };
  }

  void operator+=(Vector2& io_left, const Vector2& i_right)
  {
    io_left.x += i_right.x;
    io_left.y += i_right.y;
  }


  Vector2 operator-(const Vector2& i_left, const Vector2& i_right)
  {
    return { i_left.x - i_right.x, i_left.y - i_right.y };
  }


  Vector2 operator*(const Vector2& i_v, float i_mul)
  {
    return { i_v.x * i_mul, i_v.y * i_mul };
  }


  float length(const Vector2& i_v)
  {
    return std::sqrtf(lengthSq(i_v));
  }

  float lengthSq(const Vector2& i_v)
  {
    return i_v.x * i_v.x + i_v.y * i_v.y;
  }

  Vector2 normalize(const Vector2& i_v)
  {
    float d = length(i_v);
    return { i_v.x / d, i_v.y / d };
  }


  float dot(const Vector2& i_v1, const Vector2& i_v2)
  {
    return i_v1.x * i_v2.x + i_v1.y * i_v2.y;
  }


  Vector2 rotate(const Vector2& i_v, float i_angle)
  {
    auto cos = std::cos(i_angle);
    auto sin = std::sin(i_angle);

    return { i_v.x * cos - i_v.y * sin, i_v.x * sin + i_v.y * cos };
  }


  std::string toString(const Vector2& i_v)
  {
    return "X: " + std::to_string(i_v.x) + "Y: " + std::to_string(i_v.y);
  }


  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Vector3
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector3 operator+(const Vector3& i_left, const Vector3& i_right)
  {
    return { i_left.x + i_right.x, i_left.y + i_right.y, i_left.z + i_right.z };
  }

  Vector3 operator-(const Vector3& i_left, const Vector3& i_right)
  {
    return { i_left.x - i_right.x, i_left.y - i_right.y, i_left.z - i_right.z };
  }


  Vector3 operator+=(Vector3& i_left, const Vector3& i_right)
  {
    i_left.x += i_right.x;
    i_left.y += i_right.y;
    i_left.z += i_right.z;
    return i_left;
  }

  Vector3 operator-=(Vector3& i_left, const Vector3& i_right)
  {
    i_left.x -= i_right.x;
    i_left.y -= i_right.y;
    i_left.z -= i_right.z;
    return i_left;
  }


  Vector3 operator-(const Vector3& i_v)
  {
    return { -i_v.x, -i_v.y, -i_v.z };
  }


  Vector3 operator*(const Vector3& i_v, float i_mul)
  {
    return { i_v.x * i_mul, i_v.y * i_mul, i_v.z * i_mul };
  }

  Vector3 operator/(const Vector3& i_v, float i_mul)
  {
    return i_v * (1 / i_mul);
  }


  float length(const Vector3& i_v)
  {
    return std::sqrtf(lengthSq(i_v));
  }

  float lengthSq(const Vector3& i_v)
  {
    return i_v.x * i_v.x + i_v.y * i_v.y + i_v.z * i_v.z;
  }

  Vector3 normalize(const Vector3& i_v)
  {
    float d = length(i_v);
    return { i_v.x / d, i_v.y / d, i_v.z / d };
  }


  Vector3 cross(const Vector3& i_left, const Vector3& i_right)
  {
    return {
      i_left.y * i_right.z - i_left.z * i_right.y,
      i_left.z * i_right.x - i_left.x * i_right.z,
      i_left.x * i_right.y - i_left.y * i_right.x };
  }


  std::string toString(const Vector3& i_v)
  {
    return "X: " + std::to_string(i_v.x) + "Y: " + std::to_string(i_v.y) + "Z: " + std::to_string(i_v.z);
  }


  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Common
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector2 xyz2xz(const Vector3& i_v)
  {
    return Vector2{ i_v.x, i_v.z };
  }

  Vector3 xy2x0z(const Vector2& i_v, float i_y /* = 0.0f */)
  {
    return  Vector3{ i_v.x, i_y, i_v.y };
  }

} // ns Sdk
