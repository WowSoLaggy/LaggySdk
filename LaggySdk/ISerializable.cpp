#include "stdafx.h"
#include "ISerializable.h"

#include "Contracts.h"
#include "SerializableObject.h"


namespace Sdk
{
  const SerializableFields& ISerializable::getFields() const
  {
    return d_fields;
  }


  void ISerializable::pushObject(const std::string& i_name, ISerializable& i_serializableObject) const
  {
    d_fields.push_back(std::make_shared<SerializableObject>(i_name, i_serializableObject));
  }

} // ns Sdk
