#include "stdafx.h"
#include "Cursor.h"

#include "Window.h"


namespace Sdk
{
  void setCursorToCenter(const Window& i_window)
  {
    const int posX = i_window.getPosition().x + i_window.getResolution().x / 2;
    const int posY = i_window.getPosition().y + i_window.getResolution().y / 2;

    SetCursorPos(posX, posY);
  }

} // ns Sdk
