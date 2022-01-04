#pragma once

#include "SdkFwd.h"


namespace Sdk
{
  class ITransition
  {
  public:
    virtual ~ITransition() = default;

    virtual std::shared_ptr<IState> getSourceState() const = 0;
    virtual std::shared_ptr<IState> getDestState() const = 0;
  };

} // ns Sdk
