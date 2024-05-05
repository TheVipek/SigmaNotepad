//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <memory>
#include <SDL_render.h>

#include "SigmaObject.h"
#include "Managers/IWindowRenderingManager.h"


class SigmaRenderableObject : public SigmaObject {
public:
    SigmaRenderableObject(const SDL_Rect& rect, const bool enabled, const bool visible
        , std::shared_ptr<IWindowRenderingManager> targetWindow);
    ~SigmaRenderableObject() override;

    virtual void render(SDL_Renderer* renderer) = 0;
protected:
    std::shared_ptr<IWindowRenderingManager> targetWindow;
};
#endif //SIGMARENDERABLEOBJECT_H
