#pragma once

#include <string>


namespace Sdk
{
  struct Vector2
  {
    float x;
    float y;

    static Vector2 zero() { return { 0.0f, 0.0f }; }
    static Vector2 identity() { return { 1.0f, 1.0f }; }
  };

  struct Vector3
  {
    float x;
    float y;
    float z;

    static Vector3 zero() { return { 0.0f, 0.0f, 0.0f }; }
    static Vector3 identity() { return { 1.0f, 1.0f, 1.0f }; }
  };

  struct Vector4
  {
    float x;
    float y;
    float z;
    float w;

    static Vector4 zero() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
    static Vector4 identity() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
  };


  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Vector2
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector2 operator+(const Vector2& i_left, const Vector2& i_right);
  Vector2 operator-(const Vector2& i_left, const Vector2& i_right);

  Vector2 operator*(const Vector2& i_v, float i_mul);

  float length(const Vector2& i_v);
  float lengthSq(const Vector2& i_v);
  Vector2 normalize(const Vector2& i_v);

  float dot(const Vector2& i_v1, const Vector2& i_v2);

  Vector2 rotate(const Vector2& i_v, float i_angle);

  std::string toString(const Vector2& i_v);


  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Vector3
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector3 operator+(const Vector3& i_left, const Vector3& i_right);
  Vector3 operator-(const Vector3& i_left, const Vector3& i_right);

  Vector3 operator+=(Vector3& i_left, const Vector3& i_right);
  Vector3 operator-=(Vector3& i_left, const Vector3& i_right);

  Vector3 operator-(const Vector3& i_v);

  Vector3 operator*(const Vector3& i_v, float i_mul);
  Vector3 operator/(const Vector3& i_v, float i_mul);

  float length(const Vector3& i_v);
  float lengthSq(const Vector3& i_v);
  Vector3 normalize(const Vector3& i_v);

  Vector3 cross(const Vector3& i_left, const Vector3& i_right);

  std::string toString(const Vector3& i_v);


  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Common
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


  Vector2 xyz2xz(const Vector3& i_v);
  Vector3 xy2x0z(const Vector2& i_v, float i_y = 0.0f);

} // ns Sdk
