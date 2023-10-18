#include "stdafx.h"
#include "Contracts.h"


namespace Sdk
{
  DxException::DxException(
    const std::string& i_location, const std::string& i_line, const std::string& i_errorMsg)
    : std::runtime_error(
      i_location + "\n" +
      (!i_line.empty() ? i_line + "\n" : "") +
      (i_errorMsg.empty() ? "" : "Error message: " + i_errorMsg))
  {
  }


  AssertFailedException::AssertFailedException(
    const std::string& i_location, const std::string& i_line, const std::string& i_errorMsg)
    : DxException(i_location, "Assert failed: " + i_line, i_errorMsg)
  {
  }


  DereferenceFailedException::DereferenceFailedException(
    const std::string& i_location, const std::string& i_line, const std::string& i_errorMsg)
    : DxException(i_location, "Dereference failed: " + i_line, i_errorMsg)
  {
  }


  PreconditionFailedException::PreconditionFailedException(
    const std::string& i_location, const std::string& i_line, const std::string& i_errorMsg)
    : DxException(i_location, "Precondition failed: " + i_line, i_errorMsg)
  {
  }


  PostconditionFailedException::PostconditionFailedException(
    const std::string& i_location, const std::string& i_line, const std::string& i_errorMsg)
    : DxException(i_location, "Postcondition failed: " + i_line, i_errorMsg)
  {
  }


  DeadEndException::DeadEndException(
    const std::string& i_location, const std::string& i_errorMsg)
    : DxException(i_location, "Dead end is reached.", i_errorMsg)
  {
  }

} // ns Sdk
