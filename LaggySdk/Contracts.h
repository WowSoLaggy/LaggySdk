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

  class DereferenceFailedException : public std::runtime_error
  {
  public:
    DereferenceFailedException()
      : std::runtime_error("Dereference failed")
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

  class DeadEndException : public std::runtime_error
  {
  public:
    DeadEndException()
      : std::runtime_error("Dead end is reached")
    {
    }
  };

} // ns Sdk


#define CONTRACT_ASSERT(condition) do { \
  if (!(condition)) throw Sdk::AssertFailedException(); \
} while (false);

#define CONTRACT_EXPECT(condition) do { \
  if (!(condition)) throw Sdk::PreconditionFailedException(); \
} while (false);

#define CONTRACT_ENSURE(condition) do { \
  if (!(condition)) throw Sdk::PostconditionFailedException(); \
} while (false);

#define CONTRACT_THROW do { \
  throw Sdk::DeadEndException(); \
} while (false);


#define SAFE_DEREF(x) [&]() -> auto& { if (x) return *(x); else throw Sdk::DereferenceFailedException(); }()
