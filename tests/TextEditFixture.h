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

        defaultRect = new SDL_Rect {0,0,100,100};
        obj = new TextEdit(*defaultRect, nullptr);
    }
    void TearDown() override {
        delete defaultRect;
        delete obj;
    }
};



#endif //TEXTEDITFIXTURE_H
