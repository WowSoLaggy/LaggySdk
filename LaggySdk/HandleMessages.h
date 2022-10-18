#pragma once

#include "HandleResult.h"
#include "Message.h"


namespace Sdk
{
  using MessageHandler = std::function<HandleResult(Message)>;

  bool handleMessages(MessageHandler i_messageHandler);

} // ns Sdk
