//
// Created by thevi on 5/27/2024.
//

#ifndef TEXTEDITFIXTURE_H
#define TEXTEDITFIXTURE_H

#include "gtest/gtest.h"
#include "Renderer/TextEdit.h"

class TextEditFixture : public ::testing::Test {
protected:
    TextEdit* obj;
    SDL_Rect* defaultRect;
    void SetUp() override {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        defaultRect = new SDL_Rect {0,0,100,100};
        obj = new TextEdit(*defaultRect, nullptr);
    }
    void TearDown() override {
        delete defaultRect;
        delete obj;
        SDL_Quit();
        TTF_Quit();
    }
};



#endif //TEXTEDITFIXTURE_H
