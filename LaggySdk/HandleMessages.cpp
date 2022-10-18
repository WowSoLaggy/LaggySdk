#include "stdafx.h"
#include "HandleMessages.h"


namespace Sdk
{
  bool handleMessages(MessageHandler i_messageHandler)
  {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      const auto handleResult = i_messageHandler({
        static_cast<uint64_t>(msg.message),
        static_cast<uint64_t>(msg.wParam),
        static_cast<int64_t>(msg.lParam) });

      if (handleResult == Sdk::HandleResult::Quit)
        return false;

      if (handleResult == Sdk::HandleResult::DispatchFurther)
        DispatchMessage(&msg);
    }

    return true;
  }

} // ns Sdk
