//
// Created by thevi on 5/6/2024.
//

#ifndef ITEXT_H
#define ITEXT_H

#include <string>
#include "Font.h"

class IText : public ITextAligment {
public:
    virtual ~IText() = default;
    virtual void initFont(const std::string& fPath, const int fSize) {
        if(font != nullptr) {
            //Ignore, font has been initialized already
        }
        else {
            font = std::make_unique<Font>(fPath, fSize);
        }
    }
    virtual void setText(const std::string& text) = 0;
    virtual std::string getText() = 0;

protected:
    //i wont define there data structure for text, beacuse i may want to have different in specific scenarios
    SDL_Color                           textColor = { 242, 242, 242, 255 };
    std::unique_ptr<Font>               font;
    const std::string                   DEFAULT_FONTP = "assets/defaultFonts/OpenSans_Condensed-Medium.ttf";
    const int                           DEFAULT_FONTS = 20;
};

#endif //ITEXT_H
