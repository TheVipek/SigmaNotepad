//
// Created by thevi on 5/2/2024.
//

#ifndef WINDOWRENDERINGMANAGER_H
#define WINDOWRENDERINGMANAGER_H

#include <SDL.h>
#include <queue>

#include "IWindowRenderingManager.h"
#include "Renderer/SigmaRenderableObject.h"


class WindowRenderingManager : public IWindowRenderingManager{
public:
    WindowRenderingManager() = default;
    ~WindowRenderingManager() override {
        if(targetRenderer != nullptr) {
            SDL_DestroyRenderer(targetRenderer);
            targetRenderer = nullptr;
        }
        if(targetWindow != nullptr) {
            SDL_DestroyWindow(targetWindow);
            targetWindow = nullptr;
        }

        for(auto obj : renderableObjects) {
            delete obj;
        }
        renderableObjects.clear();
    }
    void HandleEvent(const SDL_Event& event);
    void RenderFrame();
    void AddRenderableObject(SigmaRenderableObject* obj) override;
    void RemoveRenderableObject(SigmaRenderableObject* obj) override;
    void SetTargetWindow(SDL_Window* w);
    void SetTargetRenderer(SDL_Renderer* r);
    SDL_Window* targetWindow;
    SDL_Renderer* targetRenderer;
protected:
    std::vector<SigmaRenderableObject*> renderableObjects;
};

#endif //WINDOWRENDERINGMANAGER_H
