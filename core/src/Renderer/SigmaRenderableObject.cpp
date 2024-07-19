//
// Created by thevi on 5/2/2024.
//
#include <utility>

#include "Renderer/SigmaRenderableObject.h"

#include <iostream>

SigmaRenderableObject::SigmaRenderableObject(SDL_Rect& rect, Window* _owner)
    : SigmaObject(rect,_owner) {
    if(owner != nullptr) {
        owner->addRenderableObject(this);
        owner->addEventObject(this);
    }
}
SigmaRenderableObject::~SigmaRenderableObject() {
}

void SigmaRenderableObject::handleEvent(const SDL_Event &e) {
    SigmaObject::handleEvent(e);
}
