//
// Created by thevi on 5/2/2024.
//
#include "Renderer/Font.h"

Font::Font(const std::string& fontPath, const int fontSize) : mFont(nullptr) {
    open(fontPath, fontSize);
}

Font::~Font() {
    close();
}

void Font::open(const std::string& fontPath, const int fontSize) {
    mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!mFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}
void Font::close() {
    if (mFont) {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
}
void Font::change(const std::string& fontPath, const int fontSize) {
    close();
    open(fontPath, fontSize);

}