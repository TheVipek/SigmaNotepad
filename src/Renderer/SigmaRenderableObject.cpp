//
// Created by thevi on 5/2/2024.
//
#include <utility>

#include "Renderer/SigmaRenderableObject.h"

#include <iostream>

SigmaRenderableObject::SigmaRenderableObject(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow)
    : SigmaObject(rect), targetWindow(targetWindow){
    if(targetWindow != nullptr) {
        targetWindow->AddRenderableObject(this);
    }
}
SigmaRenderableObject::~SigmaRenderableObject() {
    if(targetWindow != nullptr) {
        targetWindow->RemoveRenderableObject(this);
    }
}
void SigmaRenderableObject::render(SDL_Renderer* renderer) {
    if(isAnchorDirty) {
        int w,h;
        if(SDL_GetRendererOutputSize(renderer, &w, &h) == 0) {
            std::cout << "update anchor";
            handlePosition(w,h);
            isAnchorDirty = false;
        }
    }
}
void SigmaObject::handleEvent(const SDL_Event &e) {
    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
        std::cout << "resized";
        isAnchorDirty = true;
    }
}
