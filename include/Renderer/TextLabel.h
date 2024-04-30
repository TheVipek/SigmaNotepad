//
// Created by thevi on 4/30/2024.
//

#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <SDL_rect.h>

#include "SigmaRenderableObject.h"

enum class HorizontalAligment {
    Top,
    Center,
    Bottom
};

enum class VerticalAligment {
    Left,
    Center,
    Right
};

class TextLabel : SigmaRenderableObject {
public:
    TextLabel(const SDL_Rect& rect, SDL_Renderer& renderer
        , const bool enabled, const bool visible, const std::string& text
        , const HorizontalAligment ha = HorizontalAligment::Top, const VerticalAligment va = VerticalAligment::Left)
        : SigmaRenderableObject(rect, enabled, visible, renderer), text(text)
        , horizontal_aligment(ha), vertical_aligment(va){}


    virtual void setText(const std::string& text) { this->text = text; }
    virtual std::string getText() { return text;}

    void handleEvent(const SDL_Event &e) override;
    void render() override;
protected:
    std::string             text;
    HorizontalAligment      horizontal_aligment;
    VerticalAligment        vertical_aligment;
};

#endif //TEXTLABEL_H
