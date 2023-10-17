#pragma once

#include "SdkFwd.h"
#include "SerializableBase.h"


namespace Sdk
{
  class SerializableObject : public SerializableBase
  {
  public:
    SerializableObject(std::string i_name, ISerializable& i_serializableObject);

    virtual void serialize(Json::Value& a_json) const override;
    virtual void deserialize(const Json::Value& i_json) const override;

  private:
    ISerializable& d_serializableObject;
  };

} // ns Sdk
