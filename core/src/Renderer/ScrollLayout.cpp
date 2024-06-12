//
// Created by thevi on 6/4/2024.
//

#include "Renderer/ScrollLayout.h"

void ScrollLayout::handleEvent(const SDL_Event &e) {
    if(assignedObject == nullptr)
        return;

    assignedObject->handleEvent(e);

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
                lastMousePosY = mousePosY;
            }
        }
        if(horizontal) {
            withinX = mousePosX > currentHorizontalBarPos.x && mousePosX < currentHorizontalBarPos.x + currentHorizontalBarPos.w;
            withinY = mousePosY > currentHorizontalBarPos.y && mousePosY < currentHorizontalBarPos.y + currentHorizontalBarPos.h;

            if(withinX && withinY) {
                dragHorizontally = true;
                lastMousePosX = mousePosX;
            }
        }
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        printf("DRAGGING FALSE \n");
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

        if (dragVertically) {
            int deltaY = mouseY - lastMousePosY;
            lastMousePosY = mouseY;
            currentVerticalValue += ((float)deltaY / h);

            currentVerticalValue = std::clamp(currentVerticalValue, minValue, maxValue);
        }

        if (dragHorizontally) {
            int deltaX = mouseX - lastMousePosX;
            lastMousePosX = mouseX;
            currentHorizontalValue += ((float)deltaX / w);

            currentHorizontalValue = std::clamp(currentHorizontalValue, minValue, maxValue);
        }
    }

}

void ScrollLayout::render(SDL_Renderer *renderer){
    if(!visible)
        return;
    SigmaRenderableObject::render(renderer);
    if(assignedObject == nullptr)
        return;

    std::cout << "ContntSize;" << contentSize.w << ":" << contentSize.h << "\n";
    std::cout << "assignedObject;" << assignedObject->getWidth() << ":" << assignedObject->getHeight() << "\n";

    auto contentSize = assignedObject->getContentSize();

    SDL_Rect sourceRect = { currentHorizontalBarPos.x, currentVerticalBarPos.y, assignedObject->getWidth(), assignedObject->getHeight() };
    std::cout << "sourceRect;" << "x;" << sourceRect.x << "y;" << sourceRect.y;
    SDL_RenderSetClipRect(renderer, &sourceRect);
    assignedObject->render(renderer);
    SDL_RenderSetClipRect(renderer, nullptr);


    if(horizontal == true && contentSize.w > assignedObject->getWidth()) {
        SDL_SetRenderDrawColor(renderer, 242,242,242,255);
        int targetWidth = static_cast<int>(assignedObject->getWidth() * barSize);
        int targetY = assignedObject->getY() + assignedObject->getHeight() - DEFAULT_VERTICAL_BAR_WIDTH;
        int targetX = assignedObject->getX() + static_cast<int>((assignedObject->getWidth() - targetWidth) * currentHorizontalValue);
        currentHorizontalBarPos = { targetX, targetY, targetWidth, DEFAULT_VERTICAL_BAR_WIDTH  };
        SDL_RenderFillRect(renderer, &currentHorizontalBarPos);
    }

    if(vertical == true && contentSize.h > assignedObject->getHeight()) {
        SDL_SetRenderDrawColor(renderer, 242,242,242,255);
        int targetHeight = static_cast<int>(assignedObject->getHeight() * barSize);
        int targetX = assignedObject->getX() + (assignedObject->getWidth() - DEFAULT_HORIZONTAL_BAR_HEIGHT);
        int targetY = assignedObject->getY() + static_cast<int>((assignedObject->getHeight() - targetHeight) * currentVerticalValue);
        currentVerticalBarPos = { targetX, targetY, DEFAULT_HORIZONTAL_BAR_HEIGHT, targetHeight  };
        SDL_RenderFillRect(renderer, &currentVerticalBarPos);
    }


}

void ScrollLayout::assign(SigmaRenderableObject* targetObject) {
    assignedObject = targetObject;
    targetWindow.get()->RemoveRenderableObject(assignedObject);
}