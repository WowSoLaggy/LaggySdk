#pragma once

#include <mutex>


namespace Sdk
{
  class ILockable
  {
  public:
    virtual ~ILockable() = default;

    void lock() { d_lock.lock(); }
    void unlock() { d_lock.unlock(); }

  private:
    std::mutex d_lock;
  };

} // ns Sdk
