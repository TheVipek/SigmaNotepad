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
    Font(const std::string& fontPath, const int fontSize);
    ~Font();

    void open(const std::string& fontPath, const int fontSize);
    void close();
    void change(const std::string& fontPath, const int fontSize);

    [[nodiscard]] TTF_Font* get() const { return mFont; }

private:
    TTF_Font* mFont;

};

#endif //FONT_H
