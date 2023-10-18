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
    DxException(const std::string& i_location, const std::string& i_line = "", const std::string& i_errorMsg = "");
  };


  class AssertFailedException : public DxException
  {
  public:
    AssertFailedException(const std::string& i_location, const std::string& i_line = "", const std::string& i_errorMsg = "");
  };

  class DereferenceFailedException : public DxException
  {
  public:
    DereferenceFailedException(const std::string& i_location, const std::string& i_line = "", const std::string& i_errorMsg = "");
  };

  class PreconditionFailedException : public DxException
  {
  public:
    PreconditionFailedException(const std::string& i_location, const std::string& i_line = "", const std::string& i_errorMsg = "");
  };

  class PostconditionFailedException : public DxException
  {
  public:
    PostconditionFailedException(const std::string& i_location, const std::string& i_line = "", const std::string& i_errorMsg = "");
  };

  class DeadEndException : public DxException
  {
  public:
    DeadEndException(const std::string& i_location, const std::string& i_errorMsg = "");
  };

} // ns Sdk


#define CONTRACT_ASSERT(condition, ...) do { \
  if (!(condition)) throw Sdk::AssertFailedException(LOCATION, #condition, ##__VA_ARGS__); \
} while (false);

#define CONTRACT_EXPECT(condition, ...) do { \
  if (!(condition)) throw Sdk::PreconditionFailedException(LOCATION, #condition, ##__VA_ARGS__); \
} while (false);

#define CONTRACT_ENSURE(condition, ...) do { \
  if (!(condition)) throw Sdk::PostconditionFailedException(LOCATION, #condition, ##__VA_ARGS__); \
} while (false);

#define CONTRACT_THROW(...) do { \
  throw Sdk::DeadEndException(LOCATION, ##__VA_ARGS__); \
} while (false);


#define SAFE_DEREF(x, ...) ([&]() -> auto& { if (x) return *(x); else throw Sdk::DereferenceFailedException(LOCATION, #x, ##__VA_ARGS__); }())
