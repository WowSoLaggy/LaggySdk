#pragma once

#include "json.h"
#include "Vector.h"


namespace Sdk
{
  template <typename T>
  void writeJson(Json::Value& a_json, const T& i_value)
  {
    a_json = i_value;
  }

  template <typename T>
  void writeJson(Json::Value& a_json, const Sdk::Vector2<T>& i_value)
  {
    a_json["x"] = i_value.x;
    a_json["y"] = i_value.y;
  }

  template <typename T>
  void writeJson(Json::Value& a_json, const Sdk::Vector3<T>& i_value)
  {
    a_json["x"] = i_value.x;
    a_json["y"] = i_value.y;
    a_json["z"] = i_value.z;
  }

  template <typename T>
  void writeJson(Json::Value& a_json, const Sdk::Vector4<T>& i_value)
  {
    a_json["x"] = i_value.x;
    a_json["y"] = i_value.y;
    a_json["z"] = i_value.z;
    a_json["w"] = i_value.w;
  }

} // ns Sdk
