//
// Created by thevi on 6/4/2024.
//

#include "Renderer/ScrollLayout.h"

void ScrollLayout::handleEvent(const SDL_Event &e) {
    if(assignedObject == nullptr)
        return;
    if(!vertical && !horizontal)
        return;


    if(e.type == SDL_MOUSEBUTTONDOWN) {
        const int mousePosX = e.button.x;
        const int mousePosY = e.button.y;

        bool withinX = mousePosX > currentRect.x && mousePosX < currentRect.x + currentRect.w;
        bool withinY = mousePosY > currentRect.y && mousePosY < currentRect.y + currentRect.h;

        if(vertical) {
            withinX = mousePosX > currentVerticalBarPos.x && mousePosX < currentVerticalBarPos.x + currentVerticalBarPos.w;
            withinY = mousePosY > currentVerticalBarPos.y && mousePosY < currentVerticalBarPos.y + currentVerticalBarPos.h;

            if(withinX && withinY) {
                dragVertically = true;
                lastMousePosX = mousePosX;
            }
        }
        if(horizontal) {
            withinX = mousePosX > currentHorizontalBarPos.x && mousePosX < currentHorizontalBarPos.x + currentHorizontalBarPos.w;
            withinY = mousePosY > currentHorizontalBarPos.y && mousePosY < currentHorizontalBarPos.y + currentHorizontalBarPos.h;

            if(withinX && withinY) {
                dragHorizontally = true;
                lastMousePosX = mousePosY;
            }
        }
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        dragHorizontally = false;
        dragVertically = false;
    }


    if(!dragVertically && !dragHorizontally)
        return;

   if((dragHorizontally || dragVertically) && e.type == SDL_MOUSEMOTION) {
       float mouseX = e.motion.x;
       float mouseY = e.motion.y;

       int w;
       int h;
       SDL_GetWindowSize(targetWindow->targetWindow, &w, &h);

        // if (dragVertically) {
        //
        //
        //
        //     scrollY += deltaY * (contentSize.h / getHeight()); // adjust the scrolling speed as needed
        //     scrollY = std::clamp(scrollY, 0, std::max(0, contentSize.h - getHeight()));
        //     lastMouseY = mouseY;
        // }

        if (dragHorizontally) {
            int deltaX = mouseX - lastMousePosX;
            lastMousePosX = mouseX;
            std::cout << "deltaValue;" << deltaX << "\n";
            currentValue += deltaX / (float)w;

            currentValue = std::clamp(currentValue, minValue, maxValue);
            std::cout << "currentValue;" << currentValue << "\n";
        }
    }

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

        int targetWidth = static_cast<int>(assignedObject->getWidth() * barSize);
        int targetY = assignedObject->getY() + assignedObject->getHeight() - DEFAULT_VERTICAL_BAR_WIDTH;
        int targetX = assignedObject->getX() + static_cast<int>((assignedObject->getWidth() - targetWidth) * currentValue);
        currentHorizontalBarPos = { targetX, targetY, targetWidth, DEFAULT_VERTICAL_BAR_WIDTH  };
        SDL_RenderFillRect(renderer, &currentHorizontalBarPos);
    }

    // if(vertical == true && contentSize.h > assignedObject->getHeight()) {
    //     //render vertical
    //     SDL_SetRenderDrawColor(renderer, 242,242,242,255);
    //
    //     int targetX = assignedObject->getX() + assignedObject->getWidth() - DEFAULT_HORIZONTAL_BAR_HEIGHT;
    //     currentVerticalBarPos = { targetX, assignedObject->getY(),DEFAULT_HORIZONTAL_BAR_HEIGHT, static_cast<int>(assignedObject->getHeight() * barSize)  };
    //     SDL_RenderFillRect(renderer, &currentVerticalBarPos);
    // }
}

void ScrollLayout::assign(SigmaRenderableObject* targetObject) {
    assignedObject = targetObject;
}