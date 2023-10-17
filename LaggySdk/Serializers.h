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
  void readJson(const Json::Value& i_json, T& o_value)
  {
    // Don't know how to read
    CONTRACT_THROW;
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


  void readJson(const Json::Value& i_json, int& o_value);

  void readJson(const Json::Value& i_json, float& o_value);

  void readJson(const Json::Value& i_json, double& o_value);

  void readJson(const Json::Value& i_json, bool& o_value);

  void readJson(const Json::Value& i_json, std::string& o_value);


  template <typename T>
  void readJson(const Json::Value& i_json, Sdk::Vector2<T>& o_value)
  {
    readJson(i_json["x"], o_value.x);
    readJson(i_json["y"], o_value.y);
  }

  template <typename T>
  void readJson(const Json::Value& i_json, Sdk::Vector3<T>& o_value)
  {
    readJson(i_json["x"], o_value.x);
    readJson(i_json["y"], o_value.y);
    readJson(i_json["z"], o_value.z);
  }

  template <typename T>
  void readJson(const Json::Value& i_json, Sdk::Vector4<T>& o_value)
  {
    readJson(i_json["x"], o_value.x);
    readJson(i_json["y"], o_value.y);
    readJson(i_json["z"], o_value.z);
    readJson(i_json["w"], o_value.w);
  }

} // ns Sdk
