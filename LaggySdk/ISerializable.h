#pragma once

#include "SerializableField.h"
#include "SerializableObject.h"


namespace Sdk
{
  template <typename t>
  class SerializableShared;

  using SerializableFields = std::unordered_map<std::string, std::shared_ptr<SerializableBase>>;


  class ISerializable
  {
  public:
    virtual ~ISerializable() = default;

    virtual void pushFields() = 0;

    const SerializableFields& getFields() const;

  protected:
    template <typename T>
    void pushField(const std::string& i_name, T& i_data)
    {
      assertNameIsNotDuplicated(i_name);
      d_fields.insert({ i_name, std::make_shared<SerializableField<T>>(i_name, i_data) });
    }

    template <typename T>
    void pushSharedPtr(const std::string& i_name, std::shared_ptr<T>& i_data);

    void pushObject(const std::string& i_name, ISerializable& i_serializableObject);

  private:
    SerializableFields d_fields;

    void assertNameIsNotDuplicated(const std::string& i_name) const;
  };




  namespace
  {
    template <bool B> struct bool_ {};

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField(std::string i_name, T& d_data)
    {
      return getUnderlyingField_(bool_<std::is_base_of<ISerializable, T>::value>(), i_name, d_data);
    }

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<false>, std::string i_name, T& d_data)
    {
      // Not inheriting ISerializable
      return std::shared_ptr<SerializableField<T>>(i_name, d_data);
    }

    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<true>, std::string i_name, ISerializable& d_data)
    {
      // Inheriting ISerializable
      return std::make_shared<SerializableObject>(i_name, d_data);
    }

  } // anonym NS


  template <typename T>
  class SerializableShared : public SerializableBase
  {
  public:
    SerializableShared(std::string i_name, std::shared_ptr<T>& i_data)
      : d_name(std::move(i_name))
      , d_data(i_data)
    {
    }

    virtual void serialize(Json::Value& a_json) const override
    {
      if (!d_data)
        return;

      const auto base = getUnderlyingField(d_name, *d_data);
      CONTRACT_EXPECT(base);
      base->serialize(a_json);
    }

    virtual void deserialize(const Json::Value& i_json) const override
    {
      if (!d_data)
        d_data = std::make_shared<T>();

      const auto base = getUnderlyingField(d_name, *d_data);
      CONTRACT_EXPECT(base);
      base->deserialize(i_json);
    }

  private:
    std::string d_name;
    std::shared_ptr<T>& d_data;
  };




  template <typename T>
  void ISerializable::pushSharedPtr(const std::string& i_name, std::shared_ptr<T>& i_data)
  {
    assertNameIsNotDuplicated(i_name);
    d_fields.insert({ i_name, std::make_shared<SerializableShared<T>>(i_name, i_data) });
  }

} // ns Sdk
