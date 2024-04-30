//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <SDL_render.h>

#include "SigmaObject.h"

class SigmaRenderableObject : public SigmaObject {
public:
    SigmaRenderableObject(const int x, const int y, const int w
        , const int h, const bool enabled, const bool visible, SDL_Renderer& renderer)
        : SigmaObject(x, y, w, h, enabled, visible), renderer(renderer) {}

    SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible
        , SDL_Renderer& renderer)
        : SigmaObject(rect, enabled, visible), renderer(renderer) {}

    virtual void render() = 0;
protected:
    SDL_Renderer& renderer;
};
#endif //SIGMARENDERABLEOBJECT_H