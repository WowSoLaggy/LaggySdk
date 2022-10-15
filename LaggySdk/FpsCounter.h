#pragma once


namespace Sdk
{
  class FpsCounter
  {
  public:
    // Shall be called exactly once every frame
    void udpate(double i_dt);

    int fps() const;

  private:
    int d_fps = 0;
    double d_timer = 0;
    int d_framesNum = 0;
  };

} // ns Sdk
