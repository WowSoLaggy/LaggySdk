#pragma once

#include "json.h"


namespace Sdk
{
  class SerializableBase
  {
  public:
    virtual ~SerializableBase() = default;

    virtual void serialize(Json::Value& a_json) const = 0;
  };

} // ns Sdk
