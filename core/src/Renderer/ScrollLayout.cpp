//
// Created by thevi on 6/4/2024.
//

#include "Renderer/ScrollLayout.h"

#include <vector>

void ScrollLayout::handleEvent(const SDL_Event &e) {
    if(assignedObject == nullptr)
        return;



    if(!vertical && !horizontal) {
        return;
    }


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




    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
        std::cout << "resize event!" << "\n";
        if(assignedObject->getWidth() > assignedObject->getContentSize().w) {
            currentHorizontalValue = 0;
        }
        if(assignedObject->getHeight() > assignedObject->getContentSize().h) {
            currentVerticalValue = 0;
        }
    }

    if(!dragVertically && !dragHorizontally) {
        assignedObject->handleEvent(e);
        return;
    }

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

    auto contentSize = assignedObject->getContentSize();

    int sourceX = static_cast<int>(currentHorizontalValue * (contentSize.w - assignedObject->getWidth()));
    int sourceY = static_cast<int>(currentVerticalValue * (contentSize.h - assignedObject->getHeight()));

    sourceX = std::max(0, std::min(sourceX, contentSize.w - assignedObject->getWidth()));
    sourceY = std::max(0, std::min(sourceY, contentSize.h - assignedObject->getHeight()));

    SDL_Rect clipRect = { assignedObject->getX(), assignedObject->getY(), assignedObject->getWidth(), assignedObject->getHeight() };
    SDL_RenderSetClipRect(renderer, &clipRect);

    assignedObject->setRect({assignedObject->getX() - sourceX, assignedObject->getY() - sourceY, assignedObject->getWidth(), assignedObject->getHeight()});
    assignedObject->render(renderer);
    assignedObject->setRect({assignedObject->getX() + sourceX, assignedObject->getY() + sourceY, assignedObject->getWidth(), assignedObject->getHeight()});

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

void ScrollLayout::UpdateViewport(SDL_Renderer* renderer) {
    auto contentSize = assignedObject->getContentSize();

    int sourceX = static_cast<int>(currentHorizontalValue * (contentSize.w - assignedObject->getWidth()));
    int sourceY = static_cast<int>(currentVerticalValue * (contentSize.h - assignedObject->getHeight()));

    sourceX = std::max(0, std::min(sourceX, contentSize.w - assignedObject->getWidth()));
    sourceY = std::max(0, std::min(sourceY, contentSize.h - assignedObject->getHeight()));

    SDL_Rect clipRect = { assignedObject->getX(), assignedObject->getY(), assignedObject->getWidth(), assignedObject->getHeight() };
    SDL_RenderSetClipRect(renderer, &clipRect);

    assignedObject->setRect({assignedObject->getX() - sourceX, assignedObject->getY() - sourceY, assignedObject->getWidth(), assignedObject->getHeight()});
    assignedObject->render(renderer);
    assignedObject->setRect({assignedObject->getX() + sourceX, assignedObject->getY() + sourceY, assignedObject->getWidth(), assignedObject->getHeight()});

    SDL_RenderSetClipRect(renderer, nullptr);
}


void ScrollLayout::DrawBars(SDL_Renderer* renderer) {
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
