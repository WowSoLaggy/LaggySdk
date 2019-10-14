#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class Locker
  {
  public:
    Locker(ILockable& io_lockable);
    ~Locker();

  private:
    ILockable& d_lockable;
  };

} // ns Sdk
