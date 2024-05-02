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
    Font(const std::string& fontPath, const int fontSize) : mFont(nullptr) {
        open(fontPath, fontSize);
    }

    ~Font() {
        close();
    }

    [[nodiscard]] TTF_Font* get() const { return mFont; }

    void open(const std::string& fontPath, const int fontSize) {
        mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!mFont) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
    }
    void close() {
        if (mFont) {
            TTF_CloseFont(mFont);
            mFont = nullptr;
        }
    }
    void change(const std::string& fontPath, const int fontSize) {
        close();
        open(fontPath, fontSize);
    }

private:
    TTF_Font* mFont;
};

#endif //FONT_H
