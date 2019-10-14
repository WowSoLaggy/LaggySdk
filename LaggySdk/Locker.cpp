#include "stdafx.h"
#include "Locker.h"

#include "ILockable.h"


namespace Sdk
{
  Locker::Locker(ILockable& io_lockable)
    : d_lockable(io_lockable)
  {
    d_lockable.lock();
  }

  Locker::~Locker()
  {
    d_lockable.unlock();
  }

} // ns Sdk
