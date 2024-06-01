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

struct Selection {
    int          SelectionStart;
    int          SelectionEnd;
    bool IsSelecting = false;
};

struct Cursor {
    int Position = 0;
    Selection Selection = {};
    Uint32 LastTimeBlink = 0;
    const int BLINK_INTERVAL = 500;
    bool IsBlinking = false;

    Cursor() = default;
    Cursor(int pos, struct Selection sel, Uint32 lastTimeBlink, int blinkInterval, bool isBlinking)
        : Position(pos), Selection(sel), LastTimeBlink(lastTimeBlink), BLINK_INTERVAL(blinkInterval), IsBlinking(isBlinking) {}
};


class TextEdit : public SigmaRenderableObject, public IText<rope<char>>, public IBackground
{
public:
    TextEdit(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow)
        : SigmaRenderableObject(rect, targetWindow){
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    void setText(const rope<char> text) override {
        this->text = text;
    }
    rope<char> getText() override {
        return {text};
    }
    void setActive(bool value) {
        isActive = value;
    }
    bool getActive() {
        return isActive;
    }
    Cursor getCursor() {
        return {this->cursor};
    }
    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:
    bool                       isActive = false;
    Cursor                     cursor = {};
    int                        letterWidth;
    int                        letterHeight;

    virtual void handleNormalEvent(const SDL_Event& e);
    virtual bool handleCTRLEvent(const SDL_Event& e, bool isCtrlPressed);
    virtual bool handleSHIFTEvent(const SDL_Event& e, bool isShiftPressed);
    virtual bool handleSelection(const SDL_Event& e);

    virtual void handleCursorSelection(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);
    virtual void handleCursorBlinking(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);
    virtual void handleRenderingText(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);
    virtual void insertText(const char* val, const int& count);
    virtual void removeText(const int& count);
    virtual void removeSelectionText(const int& startPos, const int& count);
    int getSpaceBetweenLine() {
        if(font->get() != nullptr) {
            return TTF_FontLineSkip(font->get());
        }
        return -1;
    }
};

#endif //TEXTEDIT_H
