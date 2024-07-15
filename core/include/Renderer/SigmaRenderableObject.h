//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMARENDERABLEOBJECT_H
#define SIGMARENDERABLEOBJECT_H

#include <iostream>
#include <memory>
#include <SDL_render.h>

#include "IRenderHandler.h"
#include "SigmaObject.h"
#include "../Window/Window.h"

class SigmaRenderableObject : public SigmaObject, public IRenderHandler {
public:
    SigmaRenderableObject(SDL_Rect& rect, Window* _owner);
    ~SigmaRenderableObject() override;

    void render(SDL_Renderer* renderer) override;
    [[nodiscard]] SDL_Rect getContentSize() const { return contentSize; }
protected:
    SDL_Rect            contentSize = {};
    Window* owner;

};
#endif //SIGMARENDERABLEOBJECT_H
