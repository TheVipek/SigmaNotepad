//
// Created by thevi on 4/30/2024.
//



#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_rect.h>
#include <string>

#include "SigmaObject.h"
#include "SigmaRenderableObject.h"

class Button : public SigmaRenderableObject  {
    public:
    Button(const int x, const int y, const int w
        , const int h, const bool enabled, const bool visible, SDL_Renderer& renderer, const std::string& text)
        : SigmaRenderableObject(x, y, w, h, enabled, visible, renderer), text(text) {}

    Button(const SDL_Rect& rect, const bool enabled, const bool visible
        , SDL_Renderer& renderer, const std::string& text)
        : SigmaRenderableObject(rect, enabled, visible, renderer), text(text) {}

    virtual void setText(const std::string& text) { this->text = text; }
    virtual std::string getText() { return text;}

    void handleEvent(const SDL_Event &e) override;
    void render() override;

    protected:
    std::string     text;
    bool            isHovered = false;
};



#endif //BUTTON_H
