//
// Created by thevi on 5/6/2024.
//

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "TextLabel.h"
#include "Panel.h"
class TextEdit : public SigmaRenderableObject, public IText, public IBackground
{
public:
    TextEdit(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, std::string text)
        : SigmaRenderableObject(rect, targetWindow), text(text) {
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
    }
    void setText(const std::string& text) override { this->text = text; }
    std::string getText() override { return text;}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:
    std::string                 text; // temporary, need to write custom data structure
    bool                        isActive = false;
};

#endif //TEXTEDIT_H
