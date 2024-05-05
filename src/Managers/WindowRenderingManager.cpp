//
// Created by thevi on 5/2/2024.
//
#include "Managers/WindowRenderingManager.h"

#include <algorithm>
void WindowRenderingManager::RenderFrame() {
    if(targetRenderer == nullptr)
        return;

    // Clear the renderer with a default or background color
    SDL_SetRenderDrawColor(targetRenderer, 42, 42, 42, 255); // Black, or choose another color
    SDL_RenderClear(targetRenderer);

    for (auto obj: renderableObjects) {
        obj->render(targetRenderer);
    }

    SDL_RenderPresent(targetRenderer);
}

void WindowRenderingManager::HandleEvent(const SDL_Event &event) {
    for(auto obj : renderableObjects) {
        obj->handleEvent(event);
    }
}


void WindowRenderingManager::AddRenderableObject(SigmaRenderableObject* obj) {
    auto it = std::find(renderableObjects.begin(), renderableObjects.end(), obj);
    if (it == renderableObjects.end()) {  // Object not found
        renderableObjects.push_back(obj);
    } else {
        //skip
    }
}

void WindowRenderingManager::RemoveRenderableObject(SigmaRenderableObject* obj) {
    auto it = std::find(renderableObjects.begin(), renderableObjects.end(), obj);
    if (it == renderableObjects.end()) {  // Object not found
        //skip
    } else {
        renderableObjects.erase(it);
    }
}

void WindowRenderingManager::SetTargetWindow(SDL_Window* w) {
    targetWindow = w;
}
void WindowRenderingManager::SetTargetRenderer(SDL_Renderer* r) {
    targetRenderer = r;
}