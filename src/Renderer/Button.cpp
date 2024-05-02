//
// Created by thevi on 4/30/2024.
//

#include <iostream>
#include <Renderer/Button.h>

void Button::handleEvent(const SDL_Event &e) {
    if(!enabled) // no need to process events
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
            //Change color to hovered
            isHovered = true;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN) {
            //Change color to click
            onClick();
            isClicked = true;
        }
    }
}

void Button::render() {
    if(!visible) // no need to render
        return;
    SDL_Color bgColorToRender;
    if(isHovered) {
        bgColorToRender = hoverColor;
    }
    else if(isClicked) {
        bgColorToRender = clickColor;
    }
    else {
        bgColorToRender = normalColor;
    }
    SDL_SetRenderDrawColor(&renderer, bgColorToRender.r, bgColorToRender.g, bgColorToRender.b, bgColorToRender.a);

    SDL_RenderFillRect(&renderer, &rect);



    if(TLabel != nullptr) {
        TLabel->render();
    }
    SDL_RenderPresent(&renderer);
}

void Button::onClick() {

}
