//
// Created by thevi on 5/2/2024.
//
#include <utility>

#include "Renderer/SigmaRenderableObject.h"

#include <iostream>

SigmaRenderableObject::SigmaRenderableObject(SDL_Rect& rect, Window* _owner)
    : SigmaObject(rect), owner(_owner){
    if(owner != nullptr) {
        owner->addRenderableObject(this);
        owner->addEventObject(this);
    }
}
SigmaRenderableObject::~SigmaRenderableObject() {
}
void SigmaRenderableObject::render(SDL_Renderer* renderer) {
    if(isAnchorDirty) {
        int w,h;
        if(SDL_GetRendererOutputSize(renderer, &w, &h) == 0) {
            handlePosition(w,h);
            isAnchorDirty = false;
        }
    }
}
void SigmaObject::handleEvent(const SDL_Event &e) {
    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
        isAnchorDirty = true;
    }
}
