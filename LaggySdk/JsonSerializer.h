#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class JsonSerializer
  {
  public:
    static void serialize(ISerializable& i_serializable, const fs::path& i_path);
    static void serialize(ISerializable& i_serializable, Json::Value& a_json);

    static void deserialize(ISerializable& o_serializable, const fs::path& i_path);
    static void deserialize(ISerializable& o_serializable, const Json::Value& i_json);

  private:
    JsonSerializer() = delete;
  };

} // ns Sdk
