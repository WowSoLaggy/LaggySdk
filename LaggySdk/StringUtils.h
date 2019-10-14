#pragma once

#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>


namespace Sdk
{
  /// Trims the given string from the start (removes all spaces)
  /// Params:
  /// [out] std::string & pString	- string to trim
  static inline void trimStringLeadRef(std::string &pString)
  {
    pString.erase(pString.begin(), std::find_if(pString.begin(), pString.end(),
                                                [](int c) { return !std::isspace(c); }));
  }

  /// Trims the given string from the end (removes all spaces)
  /// Params:
  /// [out] std::string & pString	- string to trim
  static inline void trimStringTrailRef(std::string &pString)
  {
    pString.erase(std::find_if(pString.rbegin(), pString.rend(),
                               [](int c) { return !std::isspace(c); }).base(), pString.end());
  }

  /// Trims the given string (removes all spaces)
  /// Params:
  /// [out] std::string & pString	- string to trim
  static inline void trimStringRef(std::string &pString)
  {
    trimStringLeadRef(pString);
    trimStringTrailRef(pString);
  }

  /// Trims the given string from the start (removes all spaces)
  /// Params:
  /// [out] std::string pString	- string to trim
  static inline std::string trimStringLead(std::string pString)
  {
    trimStringLeadRef(pString);
    return pString;
  }

  /// Trims the given string from the end (removes all spaces)
  /// Params:
  /// [out] std::string pString	- string to trim
  static inline std::string trimStringTrail(std::string pString)
  {
    trimStringTrailRef(pString);
    return pString;
  }

  /// Trims the given string (removes all spaces)
  /// Params:
  /// [out] std::string pString	- string to trim
  static inline std::string trimString(std::string pString)
  {
    trimStringRef(pString);
    return pString;
  }


  /// Splits the given string to tokens with a given delimiter
  /// Params:
  /// [in]  const std::string & pString		- string to split
  /// [in]  char pDelimiter					- delimiter used to split the given string
  /// [out] std::vector<std::string> & pTokens	- vector of splitted tokens
  /// Returns:
  /// std::vector<std::string>					- vector of splitted tokens (reference to pTokens)
  static std::vector<std::string> & splitString(const std::string &pString, char pDelimiter, std::vector<std::string> &pTokens, bool pTrimTokens = false)
  {
    std::stringstream ss(pString);
    std::string item;
    if (pTrimTokens)
    {
      while (std::getline(ss, item, pDelimiter))
        pTokens.push_back(trimString(item));
    }
    else
    {
      while (std::getline(ss, item, pDelimiter))
        pTokens.push_back(item);
    }

    return pTokens;
  }


  /// Splits the given string to tokens with a given delimiter
  /// Params:
  /// [in] const std::string & pString	- string to split
  /// [in] char pDelimiter				- delimiter used to split the given string
  /// Returns:
  /// std::vector<std::string>				- vector of splitted tokens
  static std::vector<std::string> splitString(const std::string &pString, char pDelimiter, bool pTrimTokens = false)
  {
    std::vector<std::string> tokens;
    return splitString(pString, pDelimiter, tokens, pTrimTokens);
  }


  /// Converts the given string to the boolean value
  /// Params:
  /// [in] const std::string & pString	- string to convert
  static bool stringToBool(const std::string &pString)
  {
    std::string str = pString;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return (str.compare("true") == 0) || (str.compare("1") == 0);
  }


  /// Check whether the input string is a number (can be parsed to)
  /// Params:
  /// [in] const std::string & pString - input string to be checked
  static bool isNumber(const std::string &pString)
  {
    return (
      (!pString.empty()) &&
      (std::find_if(pString.begin(), pString.end(),
        [](char c) { return !std::isdigit(c); }) == pString.end())
      );
  }


  /// Converts string to wstring
  /// Params:
  /// [in] const std::string& i_string - string to convert
  static std::wstring getWString(const std::string& i_string)
  {
    return std::wstring(i_string.begin(), i_string.end());
  }

  /// Converts wstring to string
  /// Params:
  /// [in] const std::wstring& i_wstring - string to convert
  static std::string getString(const std::wstring& i_wstring)
  {
    return std::string(i_wstring.begin(), i_wstring.end());
  }


  /// Converts the given @i_value to the string with the given @i_precision
  /// \param[in] i_value - value to convert to the string
  /// \param[in] i_precision - precision to convert the value with
  template <typename T>
  std::string toString(const T i_value, const int i_precision = 6)
  {
    std::ostringstream out;
    out << std::setprecision(i_precision) << i_value;
    return out.str();
  }


  /// Returns a string of a given @i_length that consists of random chars [0-9, A-Z, a-z]
  static std::string generateRandomString(int i_length)
  {
    static const std::string allowed_chars {"1234567890ABCDFGHJKLMNPQRSTVWXZabcdfghjklmnpqrstvwxz"};

    static thread_local std::default_random_engine randomEngine(std::random_device{}());
    static thread_local std::uniform_int_distribution<int> randomDistribution(0, (int)allowed_chars.size() - 1);

    std::string id(i_length, '\0');

    for (std::string::value_type& c : id) {
      c = allowed_chars[randomDistribution(randomEngine)];
    }

    return id;
  }

} // ns Sdk
