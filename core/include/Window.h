//
// Created by thevi on 6/17/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include "Managers/WindowRenderingManager.h"
#include "Renderer/SigmaRenderableObject.h"

#include

class Window {
public:
    Window(std::shared_ptr<WindowRenderingManager> _manager) : manager(_manager) {

    }
    ~Window() {

    }

protected:
    std::shared_ptr<WindowRenderingManager> manager;
    std::vector<SigmaRenderableObject*> RenderableObjects;
};

#endif //WINDOW_H
