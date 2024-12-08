#include "events.hpp"
#include "event.h"
#include <fmt/base.h>
#include <spdlog/spdlog.h>
#include <strings.h>
#include <vector>
#include "../zenith.hpp"
namespace Zenith::Events {

class EventListener {
public:
  EventListener(Listener listener, EventCallback callback) {
    this->listener = listener;
    this->callback = callback;
  }
  bool fire(EventContext &ctx) { return this->callback(ctx); }

  bool operator==(Listener &rhs) { return rhs == this->listener; }

private:
  EventCallback callback;
  Listener listener;
};

static std::vector<EventListener> event_listeners[128];



i32 findListener(EventCode event_code, Listener listener){
  std::vector<EventListener> &listeners = event_listeners[event_code];

  for (i32 i = 0; i < listeners.size(); i++){
    if (listeners[i] == listener){
      return i;
    }
  }
  return -1;
}

void fireEvent(EventCode event_code, EventContext ctx){
  for (EventListener el : event_listeners[event_code]){
    if (el.fire(ctx)){
      return;
    }
  }
}


bool removeListener(EventCode event_code, Listener listener){
  i32 index = findListener(event_code, listener);
  if (index != -1){
    event_listeners[event_code].erase(event_listeners[event_code].begin() + index);
    return true;
  }
  return false;
}


bool addListener(EventCode event_code, Listener listener, EventCallback callback){
  i32 index = findListener(event_code, listener);
  if (index != -1){
    Logger::error("Tried to add a listener to an event that the listener was already listening to");
    return false;
  }
  event_listeners[event_code].push_back(EventListener(listener, callback));

  return true;
}

} // namespace Zenith::Events
