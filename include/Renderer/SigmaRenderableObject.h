//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <SDL_render.h>

#include "SigmaObject.h"


class SigmaRenderableObject : public SigmaObject {
public:
    SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible
        , SDL_Renderer& renderer);
    ~SigmaRenderableObject() override;

    virtual void render() = 0;
protected:
    SDL_Renderer& renderer;
};
#endif //SIGMARENDERABLEOBJECT_H
