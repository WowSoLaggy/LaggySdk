#pragma once


namespace Sdk
{
  // Simple class that counts the elapsed time in seconds. It's accuracy depends on the system performance counter frequency
  class Timer
  {
  public:


    // Default ctor with the system performance counter frequency check
    Timer()
    {
      QueryPerformanceFrequency((LARGE_INTEGER*)&d_freq);
    }

    // Default dtor
    virtual ~Timer() = default;


    // Starts the new timer
    void start()
    {
      QueryPerformanceCounter((LARGE_INTEGER*)&d_timeStart);
    }

    // Returns the time elapsed since the timer start, the timer doesn't stop
    double check()
    {
      QueryPerformanceCounter((LARGE_INTEGER*)&d_time);
      return (double)(d_time - d_timeStart) / (double)d_freq;
    }

    // Returns the time elapsed since the timer start and restarts the timer
    double restart()
    {
      QueryPerformanceCounter((LARGE_INTEGER*)&d_time);
      double dt = (double)(d_time - d_timeStart) / (double)d_freq;
      d_timeStart = d_time;
      return dt;
    }

  private:

    __int64 d_timeStart = 0;  // Stores start time
    __int64 d_time = 0;       // Used for calculations
    __int64 d_freq = 0;       // Stores performance counter frequency, used in calculations

  };

} // ns Sdk
