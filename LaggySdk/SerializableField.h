#pragma once

#include "SerializableBase.h"
#include "Serializers.h"


namespace Sdk
{
  template <typename T>
  class SerializableField : public SerializableBase
  {
  public:
    SerializableField(std::string i_name, T& i_data)
      : SerializableBase(std::move(i_name))
      , d_data(i_data)
    {
    }

    virtual void serialize(Json::Value& a_json) const override
    {
      writeJson(getJsonToSerializeTo(a_json), d_data);
    }

    virtual void deserialize(const Json::Value& i_json) const override
    {
      readJson(i_json, d_data);
    }

  private:
    T& d_data;
  };

} // ns Sdk
