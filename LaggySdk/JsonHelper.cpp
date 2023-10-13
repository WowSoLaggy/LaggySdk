#include "stdafx.h"
#include "JsonHelper.h"


namespace Sdk
{
  void JsonHelper::save(const Json::Value& i_root, const fs::path& i_path)
  {
    Json::StreamWriterBuilder builder;
    builder.settings_["indentation"] = "  ";

    const std::string str = Json::writeString(builder, i_root);

    std::ofstream file(i_path);
    file << str;
  }

} // ns Sdk
