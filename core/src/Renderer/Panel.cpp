//
// Created by thevi on 5/5/2024.
//

#include "Renderer/Panel.h"

void Panel::handleEvent(const SDL_Event &e) {
    if(!enabled) // no need to process events
        return;

    SigmaRenderableObject::handleEvent(e);
}

void Panel::render(SDL_Renderer *renderer) {
    if(!visible)
        return;


    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &currentRect);

}
