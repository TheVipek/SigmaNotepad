//
// Created by thevi on 4/30/2024.
//

#include <iostream>
#include <Renderer/Button.h>

void Button::handleEvent(const SDL_Event &e) {

    if(!enabled) // no need to process events
        return;

    SigmaRenderableObject::handleEvent(e);

    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        const int mousePosX = e.button.x;
        const int mousePosY = e.button.y;

        const bool withinX = mousePosX > currentRect.x && mousePosX < currentRect.x + currentRect.w;
        const bool withinY = mousePosY > currentRect.y && mousePosY < currentRect.y + currentRect.h;

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
            if(!isClicked) {
                std::cout << "clicked";
                onClick();
                isClicked = true;

            }
        }
        else if(e.type == SDL_MOUSEBUTTONUP) {
            if(isClicked) {
                isClicked = false;
            }
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    if(!visible) // no need to render
        return;

    SigmaRenderableObject::render(renderer);

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

    SDL_SetRenderDrawColor(renderer, bgColorToRender.r, bgColorToRender.g, bgColorToRender.b, bgColorToRender.a);
    SDL_RenderFillRect(renderer, &currentRect);
}

void Button::onClick() {

}

void Button::setAnchor(Anchor anchor) {
    SigmaRenderableObject::setAnchor(anchor);
    TLabel->setAnchor(anchor);
}

void Button::setRect(const SDL_Rect &rect) {
    SigmaRenderableObject::setRect(rect);
    TLabel->setRect(rect);
}

void Button::setOffset(const Offset &offset) {
    SigmaRenderableObject::setOffset(offset);
    TLabel->setOffset(offset);
}