#include "stdafx.h"
#include "Random.h"


namespace Sdk
{
  void randomize()
  {
    srand((unsigned int)time(nullptr));
  }

} // ns Sdk
