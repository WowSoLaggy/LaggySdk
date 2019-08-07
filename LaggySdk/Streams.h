#pragma once

#include <iostream>


namespace Sdk
{
  template<typename T>
  std::ostream& write(std::ostream& io_stream, const T& i_value)
  {
    return io_stream.write(reinterpret_cast<const char*>(&i_value), sizeof(i_value));
  }

} // ns Sdk
