//
// Created by thevi on 6/4/2024.
//

#include "Renderer/ScrollLayout.h"

void ScrollLayout::handleEvent(const SDL_Event &e) {

}

void ScrollLayout::render(SDL_Renderer *renderer){
    if(!visible)
        return;
    SigmaRenderableObject::render(renderer);
    if(assignedObject == nullptr)
        return;

    auto contentSize = assignedObject->getContentSize();

    if(horizontal == true && contentSize.w > assignedObject->getWidth()) {
        //render horizontal
        SDL_SetRenderDrawColor(renderer, 242,242,242,255);

        int testWidth = 10;
        int targetX = assignedObject->getX() + assignedObject->getWidth() - testWidth;
        //int targetY = assignedObject->getY() + assignedObject->getHeight();


        SDL_Rect horizontalRect = { targetX, assignedObject->getY(),testWidth, assignedObject->getHeight()  };
        SDL_RenderFillRect(renderer, &horizontalRect);
    }

    if(vertical == true && contentSize.h > assignedObject->getHeight()) {

    }
}

void ScrollLayout::assign(SigmaRenderableObject* targetObject) {
    assignedObject = targetObject;
}