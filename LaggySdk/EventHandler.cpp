#include "stdafx.h"
#include "EventHandler.h"


namespace Sdk
{
  EventHandler::~EventHandler()
  {
    disconnectFromAll();
  }


  void EventHandler::notify(const IEvent& i_event)
  {
    for (auto& client : d_clients)
      client.get().processEvent(i_event);
  }

  void EventHandler::connectTo(EventHandler& i_handler)
  {
    d_servers.push_back(i_handler);
    i_handler.d_clients.push_back(*this);
  }

  void EventHandler::disconnectFrom(EventHandler& i_handler)
  {
    auto removeHandler = [&](EventHandlerRefs& io_eventHandlers)
    {
      io_eventHandlers.erase(
        std::remove_if(io_eventHandlers.begin(), io_eventHandlers.end(), [&](const EventHandlerRef& i_ref)
      {
        return &(i_ref.get()) == &i_handler;
      }),
        io_eventHandlers.end());
    };

    removeHandler(d_servers);
    removeHandler(i_handler.d_clients);
  }

  void EventHandler::disconnectFromAll()
  {
    while (!d_servers.empty())
      disconnectFrom(d_servers.back());
  }

} // ns Sdk
