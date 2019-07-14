#include "stdafx.h"
#include "HandleMessages.h"


namespace Sdk
{
  bool handleMessages(MessageHandler i_messageHandler)
  {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        return false;

      i_messageHandler({
        static_cast<uint64_t>(msg.message),
        static_cast<uint64_t>(msg.wParam),
        static_cast<int64_t>(msg.lParam) });

      DispatchMessage(&msg);
    }

    return true;
  }

} // ns Sdk
