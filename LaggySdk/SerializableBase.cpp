#include "stdafx.h"
#include "SerializableBase.h"


namespace Sdk
{
  SerializableBase::SerializableBase(std::string i_name)
    : d_name(std::move(i_name))
  {
  }


  const std::string& SerializableBase::getName() const
  {
    return d_name;
  }


  Json::Value& SerializableBase::getJsonToSerializeTo(Json::Value& i_json) const
  {
    return d_name.empty() ? i_json : i_json[d_name];
  }

} // ns Sdk
