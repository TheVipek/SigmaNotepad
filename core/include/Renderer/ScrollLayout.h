//
// Created by thevi on 6/4/2024.
//

#ifndef SCROLLLAYOUT_H
#define SCROLLLAYOUT_H

#include <bits/algorithmfwd.h>

#include "IBackground.h"
#include "SigmaRenderableObject.h"


class ScrollLayout : public SigmaRenderableObject, IBackground {
public:
    ScrollLayout(float _barSize, SDL_Rect &rect, Window* owner)
        : SigmaRenderableObject(rect, owner), barSize(std::clamp(_barSize, 0.0f, 1.0f)){

    }

    void render(SDL_Renderer *renderer) override;
    void handleEvent(const SDL_Event &e) override;
    virtual void assign(SigmaRenderableObject* targetObject);


    ~ScrollLayout() {
        assignedObject = nullptr;
    }

protected:
    SigmaRenderableObject*  assignedObject;
    bool                    vertical = true;
    bool                    horizontal = true;
    bool                    dragHorizontally = false;
    bool                    dragVertically = false;
    const int               DEFAULT_VERTICAL_BAR_WIDTH = 10;
    const int               DEFAULT_HORIZONTAL_BAR_HEIGHT = 10;
    SDL_Rect                currentVerticalBarPos = {};
    SDL_Rect                currentHorizontalBarPos = {};
    float                   barSize;
    float                   maxValue = 1;
    float                   minValue = 0;
    float                   currentHorizontalValue = 0;
    float                   currentVerticalValue = 0;

    float                     lastMousePosX, lastMousePosY;

    virtual void DrawBars(SDL_Renderer* renderer);
    virtual void UpdateViewport(SDL_Renderer* renderer);
};


#endif //SCROLLLAYOUT_H
