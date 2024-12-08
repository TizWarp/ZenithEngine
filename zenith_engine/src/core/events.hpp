#pragma once

#include <functional>
#include "defines.hpp"
namespace Zenith::Events{


  union EventContext {

  };

  typedef void* Listener;

  typedef std::function<bool(EventContext&)> EventCallback;


  typedef u64 EventCode;

  void fireEvent(EventCode event_code, EventContext ctx);
  bool removeListener(EventCode event_code, Listener listener);
  bool addListener(EventCode event_code, Listener listener, EventCallback callback);


  enum {
    QUIT,
  };

}
