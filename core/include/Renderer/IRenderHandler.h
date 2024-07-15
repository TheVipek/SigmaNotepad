//
// Created by thevi on 6/18/2024.
//

#ifndef IRENDER_H
#define IRENDER_H
#include <SDL_render.h>

class IRenderHandler{
public:
    virtual ~IRenderHandler() = default;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void setRenderingPriority(const int priority) { renderingPrority = priority; }
    int getRenderingPriority() const { return renderingPrority; }
protected:
    int                 renderingPrority = 0;
};
#endif //IRENDER_H
