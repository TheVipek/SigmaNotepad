//
// Created by thevi on 5/3/2024.
//

#ifndef IWINDOWRENDERINGMANAGER_H
#define IWINDOWRENDERINGMANAGER_H
#include <vector>

#include "IRenderFrame.h"
#include "Window/Window.h"

class IWindowRenderingManager : public IEventHandler, public IRenderFrame {
public:
    IWindowRenderingManager() = default;
    virtual ~IWindowRenderingManager() = default;
    virtual void renderFrame() = 0;
    virtual void addWindow(std::shared_ptr<Window> obj) = 0;
    virtual void handleEvent(const SDL_Event &e) = 0;

protected:
    std::vector<std::shared_ptr<Window>> targetWindows;
};


#endif //IWINDOWRENDERINGMANAGER_H
