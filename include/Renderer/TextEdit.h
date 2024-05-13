//
// Created by thevi on 5/6/2024.
//

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <list>

#include "TextLabel.h"
#include "Panel.h"
#include <ext/rope>

using namespace __gnu_cxx;

class TextEdit : public SigmaRenderableObject, public IText, public IBackground
{
public:
    TextEdit(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, rope<char> text)
        : SigmaRenderableObject(rect, targetWindow),text(text){
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);

        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    void setText(const std::string& text) override {
        //this->text.push_back(rope<char>(text.c_str()));
        this->text = rope<char>(text.c_str());
    }
    std::string getText() override {
        // std::string t = "";
        // for (auto _text: text) {
        //     t += _text.c_str();
        // }
        // return t;
        return text.c_str();
    }

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:
    int getLengthOfColumn(const int& column);
    rope<char>                 text; // temporary, need to write custom data structure
    bool                       isActive = false;
    SDL_Renderer*              cursor;
    std::vector<int>           lines = { 0 };
    int                        currentColumn = 0;
    int                        letterWidth;
    int                        letterHeight;
};

#endif //TEXTEDIT_H
