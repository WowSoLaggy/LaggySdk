#include "stdafx.h"
#include "JsonSerializer.h"

#include "Contracts.h"
#include "ISerializable.h"
#include "json.h"
#include "JsonHelper.h"
#include "SerializableField.h"


namespace Sdk
{
  void JsonSerializer::serialize(ISerializable& i_serializable, const fs::path& i_path)
  {
    Json::Value root;

    serialize(i_serializable, root);

    Sdk::JsonHelper::save(root, i_path);
  }

  void JsonSerializer::serialize(ISerializable& i_serializable, Json::Value& a_json)
  {
    i_serializable.pushFields();
    for (const auto field : i_serializable.getFields())
      SAFE_DEREF(field).serialize(a_json);
  }

} // ns Sdk
