#pragma once

#include <mutex>


namespace Sdk
{
  class ILockable
  {
  public:
    virtual ~ILockable() = default;

    void lock() const { d_lock.lock(); }
    void unlock() const { d_lock.unlock(); }

  private:
    mutable std::mutex d_lock;
  };

} // ns Sdk
