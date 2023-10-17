#include "stdafx.h"
#include "Serializers.h"


namespace Sdk
{
  void readJson(const Json::Value& i_json, int& o_value)
  {
    o_value = i_json.asInt();
  }

  void readJson(const Json::Value& i_json, float& o_value)
  {
    o_value = i_json.asFloat();
  }

  void readJson(const Json::Value& i_json, double& o_value)
  {
    o_value = i_json.asDouble();
  }

  void readJson(const Json::Value& i_json, bool& o_value)
  {
    o_value = i_json.asBool();
  }

  void readJson(const Json::Value& i_json, std::string& o_value)
  {
    o_value = i_json.asString();
  }

} // ns Sdk
