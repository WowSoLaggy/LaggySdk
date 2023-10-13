#pragma once

#include "json.h"


namespace Sdk
{
  class JsonHelper
  {
  public:
    static void save(const Json::Value& i_root, const fs::path& i_path);

  private:
    JsonHelper() = delete;
  };

} // ns Sdk
