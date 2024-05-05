//
// Created by thevi on 4/30/2024.
//



#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <SDL_rect.h>
#include <string>

#include "SigmaObject.h"
#include "SigmaRenderableObject.h"
#include "TextLabel.h"

class Button : public SigmaRenderableObject  {
public:
    Button(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, const std::string& text)
        : SigmaRenderableObject(rect, targetWindow) {
        TLabel = std::make_unique<TextLabel>(this->rect, targetWindow, text );
    }

    std::unique_ptr<TextLabel>  TLabel;
    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;

protected:

    bool                        isHovered = false;
    bool                        isClicked = false;

    SDL_Color                   normalColor = { 255, 255, 255, 0}; // default bg color
    SDL_Color                   hoverColor = { 220, 220, 220, 48};; // bg on hover
    SDL_Color                   clickColor = { 220, 220, 220, 96};; // bg on click


    virtual void onClick();
};



#endif //BUTTON_H
