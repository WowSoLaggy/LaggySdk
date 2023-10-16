#pragma once

#include "json.h"


namespace Sdk
{
  class SerializableBase
  {
  public:
    virtual ~SerializableBase() = default;

    virtual void serialize(Json::Value& a_json) const = 0;
    virtual void deserialize(const Json::Value& i_json) const = 0;
  };

} // ns Sdk
