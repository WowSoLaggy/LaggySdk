#include "stdafx.h"
#include "JsonSerializer.h"

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
    i_serializable.clearAndPushFields();

    for (const auto& [_, field] : i_serializable.getFields())
      SAFE_DEREF(field).serialize(a_json);
  }


  void JsonSerializer::deserialize(ISerializable& o_serializable, const fs::path& i_path)
  {
    Json::Value root;
    std::ifstream file(i_path);
    file >> root;

    deserialize(o_serializable, root);
  }

  void JsonSerializer::deserialize(ISerializable& o_serializable, const Json::Value& i_json)
  {
    o_serializable.clearAndPushFields();

    for (const auto& childName : i_json.getMemberNames())
    {
      const auto& node = i_json[childName];

      const auto it = o_serializable.getFields().find(childName);
      if (it != o_serializable.getFields().end())
      {
        const auto& field = SAFE_DEREF(it->second);
        field.deserialize(node);
      }
      else
        o_serializable.onFieldNotFound(childName, node);
    }

    o_serializable.onDeserialized();
  }

} // ns Sdk
