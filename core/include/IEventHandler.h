//
// Created by thevi on 6/18/2024.
//

#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

class IEventHandler {
public:
    virtual ~IEventHandler() = default;
    virtual void handleEvent(const SDL_Event& e) = 0;
    virtual void setEventPriority(const int priority) { eventPriority = priority; }
    int getEventPriority() const { return eventPriority; }
    bool isEventHandled() const { return eventHandled; }
    virtual void setEventHandled(bool v) { eventHandled = v; }
protected:
    int                 eventPriority = 0;
    bool                eventHandled = false;
};
#endif //IEVENTHANDLER_H
