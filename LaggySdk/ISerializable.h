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
    virtual void onFieldNotFound(const std::string& i_name, const Json::Value& i_json);
    virtual void onDeserialized();

    const SerializableFields& getFields() const;
    void clearAndPushFields();

  protected:
    template <typename T>
    void pushField(const std::string& i_name, T& i_data)
    {
      assertNameIsNotDuplicated(i_name);
      d_fields.insert({ i_name, std::make_shared<SerializableField<T>>(i_name, i_data) });
    }

    void pushObject(const std::string& i_name, ISerializable& i_serializableObject);

    template <typename T>
    void pushSharedPtr(const std::string& i_name, std::shared_ptr<T>& i_data);

    template <typename T>
    void pushVector(const std::string& i_name, std::vector<T>& i_data);

  private:
    SerializableFields d_fields;

    void assertNameIsNotDuplicated(const std::string& i_name) const;
  };




  namespace
  {
    template <bool B> struct bool_ {};

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField(std::string i_name, T& d_data);

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<false>, std::string i_name, T& d_data);

    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<true>, std::string i_name, ISerializable& d_data);

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<false>, std::string i_name, std::shared_ptr<T>& d_data);

  } // anonym NS


  template <typename T>
  class SerializableShared : public SerializableBase
  {
  public:
    SerializableShared(std::string i_name, std::shared_ptr<T>& i_ptr)
      : SerializableBase(std::move(i_name))
      , d_ptr(i_ptr)
    {
    }


    virtual void serialize(Json::Value& a_json) const override
    {
      if (!d_ptr)
        return;

      const auto base = getUnderlyingField(getName(), *d_ptr);
      CONTRACT_EXPECT(base);
      base->serialize(a_json);
    }

    virtual void deserialize(const Json::Value& i_json) const override
    {
      if (!d_ptr)
        d_ptr = std::make_shared<T>();

      const auto base = getUnderlyingField(getName(), *d_ptr);
      CONTRACT_EXPECT(base);
      base->deserialize(i_json);
    }


  private:
    std::shared_ptr<T>& d_ptr;
  };


  template <typename T>
  class SerializableVector : public SerializableBase
  {
  public:
    SerializableVector(std::string i_name, std::vector<T>& i_vector)
      : SerializableBase(std::move(i_name))
      , d_vector(i_vector)
    {
    }


    virtual void serialize(Json::Value& a_json) const override
    {
      auto& arrayRootNode = getJsonToSerializeTo(a_json);

      for (T& item : d_vector)
      {
        const auto base = getUnderlyingField("", item);
        CONTRACT_EXPECT(base);

        Json::Value arrayItemNode;
        base->serialize(arrayItemNode);

        arrayRootNode.append(arrayItemNode);
      }
    }

    virtual void deserialize(const Json::Value& i_json) const override
    {
      CONTRACT_EXPECT(i_json.isArray());

      const int count = i_json.size();
      d_vector.resize(count);

      for (int i = 0; i < count; ++i)
      {
        const auto base = getUnderlyingField("", d_vector[i]);
        CONTRACT_EXPECT(base);
        base->deserialize(i_json[i]);
      }
    }


  private:
    std::vector<T>& d_vector;
  };
  



  namespace
  {
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

    template <typename T>
    std::shared_ptr<SerializableBase> getUnderlyingField_(bool_<false>, std::string i_name, std::shared_ptr<T>& d_data)
    {
      return std::make_shared<SerializableShared<T>>(i_name, d_data);
    }

  } // anonym NS




  template <typename T>
  void ISerializable::pushSharedPtr(const std::string& i_name, std::shared_ptr<T>& i_data)
  {
    assertNameIsNotDuplicated(i_name);
    d_fields.insert({ i_name, std::make_shared<SerializableShared<T>>(i_name, i_data) });
  }


  template <typename T>
  void ISerializable::pushVector(const std::string& i_name, std::vector<T>& i_data)
  {
    assertNameIsNotDuplicated(i_name);
    d_fields.insert({ i_name, std::make_shared<SerializableVector<T>>(i_name, i_data) });
  }

} // ns Sdk
