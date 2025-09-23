#pragma once


namespace Sdk
{
  using EntityId = std::int32_t;
  class EventHandler;
  class IEvent;
  class ILockable;
  class ISerializable;
  class IState;
  class ITransition;
  struct Message;
  class Registry;
  using UniqueId = std::int32_t;
  class Window;

} // ns Sdk


namespace Json
{
  class Value;

} // ns Json
