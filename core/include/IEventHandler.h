//
// Created by thevi on 6/18/2024.
//

#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

class IEventHandler {
public:
    virtual ~IEventHandler() = default;
    virtual void handleEvent(const SDL_Event& e) = 0;
};
#endif //IEVENTHANDLER_H
