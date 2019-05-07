#pragma once

#include <stdexcept>


namespace Sdk
{
  class PreconditionFailedException : public std::runtime_error
  {
  public:
    PreconditionFailedException()
      : std::runtime_error("")
    {
    }
  };

  class PostconditionFailedException : public std::runtime_error
  {
  public:
    PostconditionFailedException()
      : std::runtime_error("")
    {
    }
  };

} // ns Sdk


#define CONTRACT_EXPECT(x) do { \
  if (!(x)) throw Sdk::PreconditionFailedException(); \
} while (false);

#define CONTRACT_ENSURE(x) do { \
  if (!(x)) throw Sdk::PostconditionFailedException(); \
} while (false);
