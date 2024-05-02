//
// Created by thevi on 5/2/2024.
//

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H
#include <memory>
#include <queue>

#include "Renderer/SigmaRenderableObject.h"

class RendererManager {
public:
    RendererManager();
    static void RenderFrame();
    static void AddRenderableObject(const SigmaRenderableObject* obj);
    static void RemoveRenderableObject(const SigmaRenderableObject* obj);
protected:
    std::vector<std::unique_ptr<SigmaRenderableObject>> renderObjects;
};

#endif //RENDERERMANAGER_H
