#pragma once

#include <string>


namespace Sdk
{
  class Window
  {
  public:
    Window(int i_width, int i_height, std::string i_appName);

    HWND getHWnd() const { return d_hWnd; }

    void dispose();

    void show() const;

  private:
    std::string d_appName;
    HWND d_hWnd;
    HINSTANCE d_hInstance;
  };

} // ns Sdk
