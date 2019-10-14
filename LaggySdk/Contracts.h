#pragma once

#include <stdexcept>


namespace Sdk
{
  class AssertFailedException : public std::runtime_error
  {
  public:
    AssertFailedException()
      : std::runtime_error("Assert failed")
    {
    }
  };

  class PreconditionFailedException : public std::runtime_error
  {
  public:
    PreconditionFailedException()
      : std::runtime_error("Precondition failed")
    {
    }
  };

  class PostconditionFailedException : public std::runtime_error
  {
  public:
    PostconditionFailedException()
      : std::runtime_error("Postcondition failed")
    {
    }
  };

} // ns Sdk


#define CONTRACT_ASSERT(x) do { \
  if (!(x)) throw Sdk::AssertFailedException(); \
} while (false);

#define CONTRACT_EXPECT(x) do { \
  if (!(x)) throw Sdk::PreconditionFailedException(); \
} while (false);

#define CONTRACT_ENSURE(x) do { \
  if (!(x)) throw Sdk::PostconditionFailedException(); \
} while (false);
