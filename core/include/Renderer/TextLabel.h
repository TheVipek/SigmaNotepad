//
// Created by thevi on 4/30/2024.
//

#ifndef TEXTLABEL_H
#define TEXTLABEL_H


#include <memory>
#include <utility>

#include "SigmaRenderableObject.h"
#include "ITextAligment.h"
#include "IText.h"
#include "SDL_ttf.h"
#include "Font.h"


class TextLabel : public SigmaRenderableObject, public IText<std::string> {

public:
    TextLabel(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow)
        : SigmaRenderableObject(rect, targetWindow) {
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
        setText("");
    }

    void setText(const std::string text) override { this->text = text; }
    std::string getText() override { return text;}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
};

#endif //TEXTLABEL_H
