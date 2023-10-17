#include "stdafx.h"
#include "ISerializable.h"


namespace Sdk
{
  void ISerializable::onDeserialized()
  {
  }


  const SerializableFields& ISerializable::getFields() const
  {
    return d_fields;
  }

  void ISerializable::clearAndPushFields()
  {
    d_fields.clear();
    pushFields();
  }


  void ISerializable::pushObject(const std::string& i_name, ISerializable& i_serializableObject)
  {
    assertNameIsNotDuplicated(i_name);
    d_fields.insert({ i_name, std::make_shared<SerializableObject>(i_name, i_serializableObject) });
  }


  void ISerializable::assertNameIsNotDuplicated(const std::string& i_name) const
  {
    CONTRACT_EXPECT(!d_fields.contains(i_name));
  }

} // ns Sdk
