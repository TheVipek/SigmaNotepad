//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <iostream>
#include <memory>
#include <SDL_render.h>

#include "SigmaObject.h"
#include "Managers/IWindowRenderingManager.h"

class SigmaRenderableObject : public SigmaObject {
public:
    SigmaRenderableObject(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow);
    ~SigmaRenderableObject() override;

    virtual void render(SDL_Renderer* renderer) = 0;
    [[nodiscard]] SDL_Rect getContentSize() const { return contentSize; }
protected:
    std::shared_ptr<IWindowRenderingManager> targetWindow;
    SDL_Rect            contentSize = {};
};
#endif //SIGMARENDERABLEOBJECT_H
