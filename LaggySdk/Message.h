#pragma once

#include <cstdint>


namespace Sdk
{
  struct Message
  {
    uint64_t message;
    uint64_t wParam;
    int64_t lParam;
  };

} // ns Sdk
