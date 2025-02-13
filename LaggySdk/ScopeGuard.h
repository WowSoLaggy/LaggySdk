#pragma once


namespace Sdk
{
  template <typename T>
  class ScopeGuard
  {
  public:
    ScopeGuard(T& i_object)
      : d_object(i_object)
    {
      d_object.begin();
    }

    ~ScopeGuard()
    {
      d_object.end();
    }

  private:
    T& d_object;
  };

} // ns Sdk
