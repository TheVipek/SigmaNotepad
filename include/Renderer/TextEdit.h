//
// Created by thevi on 5/6/2024.
//

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "TextLabel.h"
#include "Panel.h"
#include <ext/rope>

using namespace __gnu_cxx;

class TextEdit : public SigmaRenderableObject, public IText, public IBackground
{
public:
    TextEdit(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, rope<char> text)
        : SigmaRenderableObject(rect, targetWindow), text(text) {
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
    }
    void setText(const std::string& text) override { this->text = rope<char>(text.c_str()); }
    std::string getText() override { return std::string(text.begin(), text.end());}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:
    rope<char>                 text; // temporary, need to write custom data structure
    bool                       isActive = false;
    SDL_Renderer*              cursor;
};

#endif //TEXTEDIT_H
