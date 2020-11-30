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

    void dispose();

    void show() const;

  private:
    std::string d_appName;
    HWND d_hWnd;
    HINSTANCE d_hInstance;
  };

} // ns Sdk
