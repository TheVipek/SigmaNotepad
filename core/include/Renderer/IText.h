//
// Created by thevi on 5/6/2024.
//

#ifndef ITEXT_H
#define ITEXT_H

#include <string>
#include "Font.h"



template<typename T>
class IText : public ITextAligment {
public:
    virtual ~IText() = default;
    virtual void initFont(const std::string& fPath, const int fSize) {
        currentSize = fSize;
        currentFontPath = fPath;
        if(font != nullptr) {
            //Ignore, font has been initialized already
        }
        else {
            font = std::make_unique<Font>(currentFontPath, currentSize);
        }
    }
    virtual void setText(const T text) = 0;
    virtual T getText() = 0;
    virtual void setSize(const int& size) {
        currentSize = size;
        if(font != nullptr) {
            font->change(currentFontPath, currentSize);
            setFontStyle(currentFontStyle);
        }
    }
    virtual int getSize() {
        return currentSize;
    }
    virtual void setFont(const std::string& path) {
        currentFontPath = path;

        if(font != nullptr) {
            font->change(currentFontPath, currentSize);
            setFontStyle(currentFontStyle);
        }

    }
    virtual std::string getFont(){
        return currentFontPath;
    }

    //https://wiki.libsdl.org/SDL2_ttf/TTF_SetFontStyle
    virtual void setFontStyle(int style) {
        currentFontStyle = style;
        TTF_SetFontStyle(font->get(), currentFontStyle);
    }

protected:
    //i wont define there data structure for text, beacuse i may want to have different in specific scenarios
    SDL_Color                           textColor = { 255, 255, 255, 255 };
    std::unique_ptr<Font>               font;
    const std::string                   DEFAULT_FONTP = std::string(ASSET_DIR) + "/defaultFonts/Consolas-Regular.ttf";
    const int                           DEFAULT_FONTS = 20;
    T                                   text = T();
    int                                 currentSize;
    std::string                         currentFontPath;
    int                                 currentFontStyle;
};

#endif //ITEXT_H
