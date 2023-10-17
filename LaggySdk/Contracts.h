#pragma once

#include <stdexcept>


#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ " : " S2(__LINE__)


namespace Sdk
{
  class DxException : public std::runtime_error
  {
  public:
    DxException(const std::string& i_text)
      : std::runtime_error(i_text)
    {
    }
  };


  class AssertFailedException : public DxException
  {
  public:
    AssertFailedException(const std::string& i_location)
      : DxException("Assert failed at " + i_location)
    {
    }
  };

  class DereferenceFailedException : public DxException
  {
  public:
    DereferenceFailedException(const std::string& i_location)
      : DxException("Dereference failed at " + i_location)
    {
    }
  };

  class PreconditionFailedException : public DxException
  {
  public:
    PreconditionFailedException(const std::string& i_location)
      : DxException("Precondition failed at " + i_location)
    {
    }
  };

  class PostconditionFailedException : public DxException
  {
  public:
    PostconditionFailedException(const std::string& i_location)
      : DxException("Postcondition failed at " + i_location)
    {
    }
  };

  class DeadEndException : public DxException
  {
  public:
    DeadEndException(const std::string& i_location)
      : DxException("Dead end is reached at " + i_location)
    {
    }
  };

} // ns Sdk


#define CONTRACT_ASSERT(condition) do { \
  if (!(condition)) throw Sdk::AssertFailedException(LOCATION); \
} while (false);

#define CONTRACT_EXPECT(condition) do { \
  if (!(condition)) throw Sdk::PreconditionFailedException(LOCATION); \
} while (false);

#define CONTRACT_ENSURE(condition) do { \
  if (!(condition)) throw Sdk::PostconditionFailedException(LOCATION); \
} while (false);

#define CONTRACT_THROW do { \
  throw Sdk::DeadEndException(LOCATION); \
} while (false);


#define SAFE_DEREF(x) ([&]() -> auto& { if (x) return *(x); else throw Sdk::DereferenceFailedException(LOCATION); }())
