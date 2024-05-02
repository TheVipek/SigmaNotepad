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
    Button(const SDL_Rect& rect, const bool enabled, const bool visible
        , SDL_Renderer& renderer, const std::string& text)
        : SigmaRenderableObject(rect, enabled, visible, renderer) {
        TLabel = std::make_unique<TextLabel>(this->rect, renderer, enabled, visible, text );
    }

    std::unique_ptr<TextLabel>  TLabel;

    virtual void setText(const std::string& text) { this->TLabel->setText(text); }
    virtual std::string getText() { return this->TLabel->getText(); }

    void handleEvent(const SDL_Event &e) override;
    void render() override;

    protected:

    bool                        isHovered = false;
    bool                        isClicked = false;

    SDL_Color                   normalColor = { 242, 242, 242, 255}; // default bg color
    SDL_Color                   hoverColor = { 242, 242, 242, 255};; // bg on hover
    SDL_Color                   clickColor = { 242, 242, 242, 255};; // bg on click


    virtual void onClick();
};



#endif //BUTTON_H
