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

struct Position {
    int Column = 0;
    int Line = 0;

    bool operator>=(const Position& other) const {
        if(Line >= other.Line && Column >= other.Column) {
            return true;
        }
        return false;
    }
};
struct Selection {
    Position          SelectionStart = {};
    Position          SelectionEnd = {};
    bool IsSelecting = false;
};
struct Cursor {
    Position        Position = {};
    Selection       Selection = {};

};


class TextEdit : public SigmaRenderableObject, public IText, public IBackground
{
public:
    TextEdit(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, rope<char> text)
        : SigmaRenderableObject(rect, targetWindow){
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
        setText(text.c_str());
    }
    void setText(const std::string& text) override {
        this->text = { rope<char>(text.c_str()) };
    }
    std::string getText() override {
        std::string t = "";
        for (auto _text: text) {
            t += _text.c_str();
        }
        return t;
    }

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:
    std::vector<rope<char>>    text = {}; // temporary, need to write custom data structure
    bool                       isActive = false;
    Cursor                     cursor = {};
    int                        letterWidth;
    int                        letterHeight;

    virtual bool handleCTRLEvent(const SDL_Event &e);
    virtual void handleSHIFTEvent(const SDL_Event &e);
    virtual void updateSelection();
};

#endif //TEXTEDIT_H
