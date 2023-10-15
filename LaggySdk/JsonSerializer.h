#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class JsonSerializer
  {
  public:
    static void serialize(ISerializable& i_serializable, const fs::path& i_path);
    static void serialize(ISerializable& i_serializable, Json::Value& a_json);

  private:
    JsonSerializer() = delete;
  };

} // ns Sdk
