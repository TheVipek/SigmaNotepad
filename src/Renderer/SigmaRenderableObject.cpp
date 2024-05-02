//
// Created by thevi on 5/2/2024.
//
#include "Renderer/SigmaRenderableObject.h"
#include "Managers/RendererManager.h"

SigmaRenderableObject::SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible
    , SDL_Renderer& renderer)
    : SigmaObject(rect, enabled, visible), renderer(renderer) {
    RendererManager::AddToQueue(this);
}
SigmaRenderableObject::~SigmaRenderableObject() {
    RendererManager::RemoveFromQueue(this);
}