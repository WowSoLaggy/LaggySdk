#include "stdafx.h"
#include "Cursor.h"


namespace Sdk
{
  void setCursorToCenter()
  {
    int posX = GetSystemMetrics(SM_CXSCREEN) / 2;
    int posY = GetSystemMetrics(SM_CYSCREEN) / 2;
    SetCursorPos(posX, posY);
  }

} // ns Sdk
