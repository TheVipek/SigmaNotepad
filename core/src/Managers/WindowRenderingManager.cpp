//
// Created by thevi on 5/2/2024.
//
#include "Managers/WindowRenderingManager.h"

#include <algorithm>
void WindowRenderingManager::renderFrame() {
    for(const auto& obj : targetWindows) {
        // Clear the renderer with a default or background color
        SDL_SetRenderDrawColor(obj->getRenderer(), 42, 42, 42, 255); // Black, or choose another color
        SDL_RenderClear(obj->getRenderer());

        obj->renderFrame();
        SDL_RenderPresent(obj->getRenderer());
    }
}

void WindowRenderingManager::handleEvent(const SDL_Event &event) {

    for(const auto& obj : targetWindows) {
        obj->handleEvent(event);
    }
}
void WindowRenderingManager::addWindow(std::shared_ptr<Window> obj) {
    targetWindows.push_back(obj);
}


