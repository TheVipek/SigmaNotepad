//
// Created by thevi on 4/30/2024.
//

#include <Renderer/Button.h>

void Button::handleEvent(const SDL_Event &e) {
    if(!enabled)
        return;

    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
        const int mousePosX = e.button.x;
        const int mousePosY = e.button.y;

        const bool withinX = mousePosX > rect.x && mousePosX < rect.x + rect.w;
        const bool withinY = mousePosY > rect.y && mousePosY < rect.y + rect.h;

        if(!withinX || !withinY) {
            if(isHovered) {
                //Change color to not hovered
                isHovered = false;
            }
            return;
        }

        if(e.type == SDL_MOUSEMOTION) {

        }
        else if(e.type == SDL_MOUSEBUTTONDOWN) {

        }
    }
}

void Button::render() {

}