#include "stdafx.h"
#include "HandleMessages.h"


namespace Sdk
{
  bool handleMessages(MessageHandler i_messageHandler)
  {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      switch (msg.message)
      {
      case WM_QUIT:
        return false;

      case WM_KEYDOWN:
      case WM_SYSKEYDOWN:
      case WM_KEYUP:
      case WM_SYSKEYUP:
        i_messageHandler({
          static_cast<uint64_t>(msg.message),
          static_cast<uint64_t>(msg.wParam),
          static_cast<int64_t>(msg.lParam) });
        break;
      }

      DispatchMessage(&msg);
    }

    return true;
  }

} // ns Sdk
