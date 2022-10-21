#pragma once

namespace Sdk
{
  /// Trims the given string from the start (removes all spaces)
  /// Params:
  /// [out] std::string& io_string - string to trim
  void trimStringLeadRef(std::string& io_string);

  /// Trims the given string from the end (removes all spaces)
  /// Params:
  /// [out] std::string& io_string - string to trim
  void trimStringTrailRef(std::string& io_string);

  /// Trims the given string (removes all spaces)
  /// Params:
  /// [out] std::string& io_string - string to trim
  void trimStringRef(std::string& io_string);

  /// Trims the given string from the start (removes all spaces)
  /// Params:
  /// [out] std::string i_string - string to trim
  std::string trimStringLead(std::string i_string);

  /// Trims the given string from the end (removes all spaces)
  /// Params:
  /// [out] std::string i_string - string to trim
  std::string trimStringTrail(std::string i_string);

  /// Trims the given string (removes all spaces)
  /// Params:
  /// [out] std::string i_string - string to trim
  std::string trimString(std::string i_string);


  /// Splits the given string to tokens with a given delimiter
  /// Params:
  /// [in]  const std::string& i_string         - string to split
  /// [in]  char i_delimiter                    - delimiter used to split the given string
  /// [out] std::vector<std::string>& io_tokens - vector of splitted tokens
  /// Returns:
  /// std::vector<std::string>                  - vector of splitted tokens (reference to pTokens)
  std::vector<std::string>& splitString(
    const std::string& i_string, char i_delimiter, std::vector<std::string>& io_tokens, bool i_trimTokens = false);


  /// Splits the given string to tokens with a given delimiter
  /// Params:
  /// [in] const std::string& i_string  - string to split
  /// [in] char i_delimiter             - delimiter used to split the given string
  /// Returns:
  /// std::vector<std::string>          - vector of splitted tokens
  std::vector<std::string> splitString(const std::string& i_string, char i_delimiter, bool i_trimTokens = false);


  /// Converts the given string to the boolean value
  /// Params:
  /// [in] const std::string& i_string - string to convert
  bool stringToBool(std::string i_string);


  /// Check whether the input string is a number (can be parsed to)
  /// Params:
  /// [in] const std::string& i_string - input string to be checked
  bool isNumber(const std::string& i_string);


  /// Converts string to wstring
  /// Params:
  /// [in] const std::string& i_string - string to convert
  std::wstring s2ws(const std::string& i_string);

  /// Converts wstring to string
  /// Params:
  /// [in] const std::wstring& i_wstring - string to convert
  std::string ws2s(const std::wstring& i_wstring);


  /// Converts the given @i_value to the string with the @i_fixed digits after point
  /// \param[in] i_value - value to convert to the string
  /// \param[in] i_fixed - number of fixed digits after point
  template <typename T>
  std::string toString(const T i_value, const int i_fixed = 2)
  {
    std::ostringstream out;
    out << std::fixed << std::setprecision(i_fixed) << i_value;
    return out.str();
  }


  /// Returns a string of a given @i_length that consists of random chars [0-9, A-Z, a-z]
  std::string generateRandomString(int i_length);

} // ns Sdk
