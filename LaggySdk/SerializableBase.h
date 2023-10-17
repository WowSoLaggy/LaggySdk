#pragma once

#include "json.h"


namespace Sdk
{
  class SerializableBase
  {
  public:
    SerializableBase(std::string i_name);
    virtual ~SerializableBase() = default;

    virtual void serialize(Json::Value& a_json) const = 0;
    virtual void deserialize(const Json::Value& i_json) const = 0;

  protected:
    const std::string& getName() const;
    Json::Value& getJsonToSerializeTo(Json::Value& i_json) const;

  private:
    std::string d_name;
  };

} // ns Sdk
