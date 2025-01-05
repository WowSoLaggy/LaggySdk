#pragma once


namespace Sdk
{
  class ICastable
  {
  public:
    virtual ~ICastable() = default;

    template <typename T>
    T* as()
    {
      return dynamic_cast<T*>(this);
    }
    template <typename T>
    const T* as() const
    {
      return dynamic_cast<const T*>(this);
    }
    template <typename T>
    T& asRef()
    {
      return dynamic_cast<T&>(*this);
    }
    template <typename T>
    const T& asRef() const
    {
      return dynamic_cast<const T&>(*this);
    }
  };

} // ns Sdk
