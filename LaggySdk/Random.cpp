#include "stdafx.h"
#include "Random.h"


namespace Sdk
{
  void randomize()
  {
    std::srand((unsigned int)time(nullptr));
  }

} // ns Sdk
