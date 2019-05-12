#pragma once

#include "Message.h"


namespace Sdk
{
  using MessageHandler = std::function<void(Message)>;

  bool handleMessages(MessageHandler i_messageHandler);

} // ns Sdk
