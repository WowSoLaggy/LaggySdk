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
      : d_name(std::move(i_name))
      , d_data(i_data)
    {
    }

    virtual void serialize(Json::Value& a_json) const override
    {
      writeJson(a_json[d_name], d_data);
    }

  private:
    std::string d_name;
    T& d_data;
  };

} // ns Sdk
