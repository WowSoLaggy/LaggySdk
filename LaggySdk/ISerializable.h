#pragma once

#include "SerializableField.h"


namespace Sdk
{
  using SerializableFields = std::vector<std::shared_ptr<SerializableBase>>;


  class ISerializable
  {
  public:
    virtual ~ISerializable() = default;

    virtual void pushFields() = 0;

    const SerializableFields& getFields() const;

  protected:
    template <typename T>
    void pushField(const std::string& i_name, T& i_data) const
    {
      d_fields.push_back(std::make_shared<SerializableField<T>>(i_name, i_data));
    }

    void pushObject(const std::string& i_name, ISerializable& i_serializableObject) const;

  private:
    mutable SerializableFields d_fields;
  };

} // ns Sdk
