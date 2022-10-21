#include "stdafx.h"
#include "StringUtils.h"


namespace Sdk
{
  void trimStringLeadRef(std::string& io_string)
  {
    io_string.erase(io_string.begin(), std::find_if(io_string.begin(), io_string.end(),
      [](int c) { return !std::isspace(c); }));
  }

  void trimStringTrailRef(std::string& io_string)
  {
    io_string.erase(std::find_if(io_string.rbegin(), io_string.rend(),
      [](int c) { return !std::isspace(c); }).base(), io_string.end());
  }

  void trimStringRef(std::string& io_string)
  {
    trimStringLeadRef(io_string);
    trimStringTrailRef(io_string);
  }

  std::string trimStringLead(std::string i_string)
  {
    trimStringLeadRef(i_string);
    return i_string;
  }

  std::string trimStringTrail(std::string i_string)
  {
    trimStringTrailRef(i_string);
    return i_string;
  }

  std::string trimString(std::string i_string)
  {
    trimStringRef(i_string);
    return i_string;
  }


  std::vector<std::string>& splitString(
    const std::string& i_string, char i_delimiter, std::vector<std::string>& io_tokens, bool i_trimTokens)
  {
    std::stringstream ss(i_string);
    std::string item;
    if (i_trimTokens)
    {
      while (std::getline(ss, item, i_delimiter))
        io_tokens.push_back(trimString(item));
    }
    else
    {
      while (std::getline(ss, item, i_delimiter))
        io_tokens.push_back(item);
    }

    return io_tokens;
  }


  std::vector<std::string> splitString(const std::string& i_string, char i_delimiter, bool i_trimTokens)
  {
    std::vector<std::string> tokens;
    return splitString(i_string, i_delimiter, tokens, i_trimTokens);
  }


  bool stringToBool(std::string i_string)
  {
    std::transform(i_string.begin(), i_string.end(), i_string.begin(), ::tolower);
    return (i_string.compare("true") == 0) || (i_string.compare("1") == 0);
  }


  bool isNumber(const std::string& i_string)
  {
    return (
      (!i_string.empty()) &&
      (std::find_if(i_string.begin(), i_string.end(),
        [](char c) { return !std::isdigit(c); }) == i_string.end())
      );
  }


  std::wstring s2ws(const std::string& i_string)
  {
    return std::wstring(i_string.begin(), i_string.end());
  }

  std::string ws2s(const std::wstring& i_wstring)
  {
    std::string str(i_wstring.length(), 0);
    std::transform(i_wstring.cbegin(), i_wstring.cend(), str.begin(), [](wchar_t c) { return (char)c; });
    return str;
  }


  std::string generateRandomString(const int i_length)
  {
    static const std::string allowed_chars{ "1234567890ABCDFGHJKLMNPQRSTVWXZabcdfghjklmnpqrstvwxz" };

    static thread_local std::default_random_engine randomEngine(std::random_device{}());
    static thread_local std::uniform_int_distribution<int> randomDistribution(0, (int)allowed_chars.size() - 1);

    std::string id(i_length, '\0');

    for (std::string::value_type& c : id) {
      c = allowed_chars[randomDistribution(randomEngine)];
    }

    return id;
  }

} // ns Sdk
