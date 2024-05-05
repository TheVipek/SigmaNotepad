//
// Created by thevi on 5/2/2024.
//
#include <utility>

#include "Renderer/SigmaRenderableObject.h"

#include <iostream>

SigmaRenderableObject::SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible
                                             , std::shared_ptr<IWindowRenderingManager> targetWindow)
    : SigmaObject(rect, enabled, visible), targetWindow(targetWindow){
    if(targetWindow != nullptr) {
        targetWindow->AddRenderableObject(this);
    }
}
SigmaRenderableObject::~SigmaRenderableObject() {
    if(targetWindow != nullptr) {
        targetWindow->RemoveRenderableObject(this);
    }
}