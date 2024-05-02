//
// Created by thevi on 5/2/2024.
//

#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Font {
public:
    Font(const std::string& fontPath, int fontSize) : mFont(nullptr) {
        mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!mFont) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
    }

    ~Font() {
        if (mFont) {
            TTF_CloseFont(mFont);
            mFont = nullptr;
        }
    }

    TTF_Font* get() const { return mFont; }

private:
    TTF_Font* mFont;
};

#endif //FONT_H
