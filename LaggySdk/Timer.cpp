#include "stdafx.h"
#include "Timer.h"


namespace Sdk
{
  Timer::Timer()
  {
    QueryPerformanceFrequency((LARGE_INTEGER*)&d_freq);
  }


  void Timer::start()
  {
    QueryPerformanceCounter((LARGE_INTEGER*)&d_timeStart);
  }

  double Timer::check() const
  {
    QueryPerformanceCounter((LARGE_INTEGER*)&d_time);
    return (double)(d_time - d_timeStart) / (double)d_freq;
  }

  double Timer::restart()
  {
    QueryPerformanceCounter((LARGE_INTEGER*)&d_time);
    double dt = (double)(d_time - d_timeStart) / (double)d_freq;
    d_timeStart = d_time;
    return dt;
  }

} // ns Sdk
