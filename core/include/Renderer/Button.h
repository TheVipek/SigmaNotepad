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
    Button(SDL_Rect& rect, Window* _owner, const std::string& text)
        : SigmaRenderableObject(rect, _owner) {

        TLabel = std::make_shared<TextLabel>(this->baseRect, owner);
        TLabel->setText(text);
    }

    std::shared_ptr<TextLabel>  TLabel;
    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
    void setRect(const SDL_Rect& rect) override;
    void setAnchor(Anchor anchor) override;
    void setOffset(const Offset &offset) override;

protected:

    bool                        isHovered = false;
    bool                        isClicked = false;

    SDL_Color                   normalColor = { 255, 255, 255, 0}; // default bg color
    SDL_Color                   hoverColor = { 220, 220, 220, 48};; // bg on hover
    SDL_Color                   clickColor = { 220, 220, 220, 96};; // bg on click


    virtual void onClick();
};



#endif //BUTTON_H
