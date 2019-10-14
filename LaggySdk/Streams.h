#pragma once

#include <iostream>


namespace Sdk
{
  template<typename T>
  std::ostream& write(std::ostream& io_stream, const T& i_value)
  {
    return io_stream.write(reinterpret_cast<const char*>(&i_value), sizeof(i_value));
  }

  template<typename T>
  std::istream& read(std::istream& io_stream, T& o_value)
  {
    return io_stream.read(reinterpret_cast<char*>(&o_value), sizeof(o_value));
  }

  static void writeString(std::ostream& io_stream, const std::string& i_string)
  {
    write(io_stream, (int)i_string.length());
    io_stream << i_string;
  }

  static std::string readString(std::istream& io_stream)
  {
    int length;
    read(io_stream, length);

    std::string str(length, ' ');
    io_stream.read(str.data(), length);

    return str;
  }

} // ns Sdk
