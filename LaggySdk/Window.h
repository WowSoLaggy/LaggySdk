#pragma once

#include "Vector.h"

#include <string>


namespace Sdk
{
  class Window final
  {
  public:
    Window(const Vector2I& i_resolution, std::string i_appName);
    ~Window();

    HWND getHWnd() const { return d_hWnd; }

    void show() const;

    const Vector2I& getResolution() const { return d_resolution; }
    const Vector2I& getPosition() const { return d_position; }

  private:
    std::string d_appName;
    Vector2I d_resolution;
    Vector2I d_position;

    HWND d_hWnd;
    HINSTANCE d_hInstance;
  };

} // ns Sdk
