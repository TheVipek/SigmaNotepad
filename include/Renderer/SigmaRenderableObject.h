//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <SDL_render.h>

#include "SigmaObject.h"

class SigmaRenderableObject : public SigmaObject {
public:
    SigmaRenderableObject(const int x, const int y, const int w, const int h, const bool enabled, const bool visible)
        : SigmaObject(x, y, w, h, enabled, visible) {}
    SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible)
        : SigmaObject(rect, enabled, visible) {}

    virtual void render(SDL_Renderer& renderer) = 0;
};
#endif //SIGMARENDERABLEOBJECT_H
