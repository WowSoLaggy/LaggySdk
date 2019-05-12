#pragma once

#include <string>


namespace Sdk
{
  class Window
  {
  public:
    Window();

    HWND getHWnd() const { return d_hWnd; }

    void create(int i_width, int i_height, const std::string& i_appName);
    void dispose();

    void show() const;

  private:
    std::string d_appName;
    HWND d_hWnd;
    HINSTANCE d_hInstance;
  };

} // ns Sdk
