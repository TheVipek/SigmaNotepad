//
// Created by thevi on 5/6/2024.
//

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <list>

#include "TextLabel.h"
#include "Panel.h"
#include <ext/rope>

#include "IEditField.h"

using namespace __gnu_cxx;

struct Selection {
    int          SelectionStart;
    int          SelectionEnd;
    bool         IsSelecting = false;
    bool         IsMousePressed = false;

    void updateSelectionStart(int pos) {
        SelectionStart = pos;
    }
    void updateSelectionEnd(int pos) {
        SelectionEnd = pos;
    }
    std::pair<int,int> getOrderedSelection() const {
        int selectionStart = SelectionStart >= SelectionEnd ?  SelectionEnd : SelectionStart;
        int selectionEnd = SelectionEnd >= SelectionStart ?  SelectionEnd : SelectionStart;
        std::cout << "selectionStart;" << selectionStart << "\n";
        std::cout << "selectionEnd;" << selectionEnd << "\n";
        return std::make_pair(selectionStart, selectionEnd);
    }
};

struct Cursor {
private:
    int Position = 0;
public:
    Uint32 LastTimeBlink = 0;
    const int BLINK_INTERVAL = 500;
    bool IsBlinking = false;
    std::function<void(const Cursor&)> onUpdateCursorPosition;

    Cursor() = default;
    Cursor(int pos, Uint32 lastTimeBlink, int blinkInterval, bool isBlinking, const std::function<void(const Cursor&)>& updateFunc)
        : Position(pos), LastTimeBlink(lastTimeBlink), BLINK_INTERVAL(blinkInterval), IsBlinking(isBlinking),onUpdateCursorPosition(updateFunc)  {}

    int getPos() const {
       return Position;
    }
    void updatePosition(const int newPos) {
        Position = newPos;
        if (onUpdateCursorPosition) {
            onUpdateCursorPosition(*this);
        }
    }

    void updateTicks(Uint32 currentTime) {
        if (currentTime - LastTimeBlink >= BLINK_INTERVAL) {
            IsBlinking = !IsBlinking;
            LastTimeBlink = currentTime;
        }
    }




};


class TextEdit : public SigmaRenderableObject, public IText<rope<char>>, public IBackground, public IEditField
{
public:
    TextEdit(SDL_Rect& rect, Window* owner)
        : SigmaRenderableObject(rect, owner){
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    ~TextEdit() {
    }
    void setText(const rope<char> text) override {
        this->text = text;
    }
    rope<char> getText() override {
        return {text};
    }
    void setSize(const int& size) override {
        IText::setSize(size);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    void setFont(const std::string& path) override {
        IText::setFont(path);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    void setFontStyle(int style) override {
        IText::setFontStyle(style);
        TTF_SizeUTF8(font->get(), " ",&letterWidth, &letterHeight);
    }
    void setActive(bool value) {
        isActive = value;
    }
    bool getActive() {
        return isActive;
    }
    Cursor getCursor() const {
        return cursor;
    }
    Selection getSelection() const {
        return selection;
    }
    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;

protected:
    bool                       isActive = false;
    Cursor                     cursor = Cursor( 0,0,500,false, std::bind(&TextEdit::onCursorUpdated, this, std::placeholders::_1));
    Selection                  selection = {};
    int                        letterWidth;
    int                        letterHeight;

    virtual void handleNormalEvent(const SDL_Event& e);
    virtual bool handleCTRLEvent(const SDL_Event& e);
    virtual void handleSHIFTEvent(const SDL_Event& e);
    virtual bool handleMouse(const SDL_Event& e);
    virtual int convertMousePositionToCharacterPosition(const int x, const int y);
    virtual void onCursorUpdated(const Cursor& cursor);
    virtual void handleSelection(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);
    virtual void handleCursorBlinking(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);
    virtual void handleRenderingText(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines);


    virtual void insertText(const char* val, const int& count);
    virtual void removeText(const int& count);
    virtual void removeSelectionText(const int& startPos, const int& count);
    virtual std::string getSelectionText(const int& startPos, const int& count);
    virtual bool copyToClipboard();
    virtual bool pasteFromClipboard();
    int getSpaceBetweenLine() {
        if(font->get() != nullptr) {
            return TTF_FontLineSkip(font->get());
        }
        return -1;
    }

};

#endif //TEXTEDIT_H
