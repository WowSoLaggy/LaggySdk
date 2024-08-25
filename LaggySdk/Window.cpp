#include "stdafx.h"
#include "Window.h"

#include "Contracts.h"
#include "MessageCodeUtils.h"


namespace Sdk
{
  namespace
  {
    HMONITOR getMonitorWithFocus()
    {
      HWND hwnd = GetForegroundWindow();
      if (!hwnd)
        return MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
      return MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    }

    LRESULT __stdcall wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
      switch (msg)
      {
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

      case WM_ACTIVATE:
      case WM_ACTIVATEAPP:
      case WM_SETFOCUS:
      case WM_KILLFOCUS:
        // These events shall be handled in our app, but are sent directly to the window -
        // redirect them to the message queue
        PostMessage(hWnd, msg, wParam, lParam);
        return 0;
      }

      return DefWindowProc(hWnd, msg, wParam, lParam);
    }

  } // Anonymous NS


  Window::Window(const Vector2I& i_resolution, std::string i_appName)
    : d_appName(std::move(i_appName))
    , d_resolution(i_resolution)
  {
    // Register win class
    
    d_hInstance = GetModuleHandle(nullptr);
    CONTRACT_ASSERT(d_hInstance);

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

    HMONITOR hMonitor = getMonitorWithFocus();
    CONTRACT_ASSERT(hMonitor);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hMonitor, &mi))
      CONTRACT_THROW();

    d_position = {
      mi.rcWork.left + (mi.rcWork.right - mi.rcWork.left - d_resolution.x) / 2,
      mi.rcWork.top + (mi.rcWork.bottom - mi.rcWork.top - d_resolution.y) / 2
    };

    d_hWnd = CreateWindowEx(0, d_appName.c_str(), d_appName.c_str(), WS_POPUP,
      d_position.x, d_position.y, d_resolution.x, d_resolution.y, nullptr, nullptr, d_hInstance, nullptr);
    CONTRACT_ASSERT(d_hWnd);
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
