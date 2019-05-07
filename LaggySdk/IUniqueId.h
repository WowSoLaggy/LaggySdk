#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class IUniqueId
  {
  public:
    IUniqueId() : d_uniqueId(s_nextUniqueId++) { }
    virtual ~IUniqueId() = default;

    UniqueId getId() const { return d_uniqueId; }

  private:
    UniqueId d_uniqueId;

  private:
    static UniqueId s_nextUniqueId;
  };

} // ns Sdk
