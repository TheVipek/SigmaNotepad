//
// Created by thevi on 5/5/2024.
//

#ifndef PANEL_H
#define PANEL_H
#include "IBackground.h"
#include "SigmaRenderableObject.h"


class Panel : public SigmaRenderableObject, public IBackground {
public:
    Panel(SDL_Rect& rect, Window* owner) : SigmaRenderableObject(rect, owner) {}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;


protected:

};

#endif //PANEL_H
