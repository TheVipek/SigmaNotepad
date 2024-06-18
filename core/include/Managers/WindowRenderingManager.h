//
// Created by thevi on 5/2/2024.
//

#ifndef WINDOWRENDERINGMANAGER_H
#define WINDOWRENDERINGMANAGER_H

#include <SDL.h>

#include "IWindowRenderingManager.h"
#include "Renderer/SigmaRenderableObject.h"

class WindowRenderingManager : public IWindowRenderingManager {
public:
    WindowRenderingManager() = default;
    ~WindowRenderingManager() override {
        targetWindows.clear();
    }
    void handleEvent(const SDL_Event& event) final;
    void renderFrame() final;
    void addWindow(std::shared_ptr<Window> obj) final;
};

#endif //WINDOWRENDERINGMANAGER_H
