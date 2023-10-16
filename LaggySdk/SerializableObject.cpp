#include "stdafx.h"
#include "SerializableObject.h"

#include "ISerializable.h"
#include "JsonSerializer.h"


namespace Sdk
{
  SerializableObject::SerializableObject(std::string i_name, ISerializable& i_serializableObject)
    : d_name(std::move(i_name))
    , d_serializableObject(i_serializableObject)
  {
  }


  void SerializableObject::serialize(Json::Value& a_json) const
  {
    JsonSerializer::serialize(d_serializableObject, a_json[d_name]);
  }

  void SerializableObject::deserialize(const Json::Value& i_json) const
  {
    JsonSerializer::deserialize(d_serializableObject, i_json);
  }

} // ns Sdk
