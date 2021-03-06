#include "stdafx.h"
#include "Window.h"


namespace Sdk
{
  namespace
  {
    LRESULT __stdcall wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
      switch (msg)
      {
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
      }
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }
  } // Anonymous NS


  Window::Window(const Vector2I& i_resolution, std::string i_appName)
    : d_appName(std::move(i_appName))
  {
    // Register win class

    d_hInstance = GetModuleHandle(nullptr);

    WNDCLASSEX wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)(6);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(d_hInstance, IDI_APPLICATION);
    wc.hIconSm = wc.hIcon;
    wc.hInstance = d_hInstance;
    wc.lpszClassName = d_appName.c_str();
    wc.lpszMenuName = nullptr;
    wc.cbSize = sizeof(WNDCLASSEX);

    ATOM atom = RegisterClassEx(&wc);

    // Create window

    int posX = (GetSystemMetrics(SM_CXSCREEN) - i_resolution.x) / 2;
    int posY = (GetSystemMetrics(SM_CYSCREEN) - i_resolution.y) / 2;

    d_hWnd = CreateWindowEx(0, d_appName.c_str(), d_appName.c_str(), WS_POPUP,
      posX, posY, i_resolution.x, i_resolution.y, nullptr, nullptr, d_hInstance, nullptr);
  }

  Window::~Window()
  {
    DestroyWindow(d_hWnd);
    UnregisterClass(d_appName.c_str(), d_hInstance);
  }


  void Window::show() const
  {
    // Bring the window up on the screen and set it as main focus.
    ShowWindow(d_hWnd, SW_SHOW);
    UpdateWindow(d_hWnd);
    SetForegroundWindow(d_hWnd);
    SetFocus(d_hWnd);
  }

} // ns Sdk
