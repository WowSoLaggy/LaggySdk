#include "stdafx.h"
#include "FpsCounter.h"


namespace Sdk
{
  void FpsCounter::udpate(double i_dt)
  {
    d_timer += i_dt;
    ++d_framesNum;

    if (d_timer >= 1)
    {
      d_fps = d_framesNum;
      d_timer = 0;
      d_framesNum = 0;
    }
  }

  int FpsCounter::fps() const
  {
    return d_fps;
  }

} // ns Sdk
