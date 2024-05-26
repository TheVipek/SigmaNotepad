//
// Created by thevi on 5/26/2024.
//

#ifndef SIGMAOBJECTFIXTURE_H
#define SIGMAOBJECTFIXTURE_H

#include "gtest/gtest.h"
#include "Renderer/SigmaObject.h"

class SigmaObjectFixture : public ::testing::Test {
protected:
    const int defaultScreenWidth = 800;
    const int defaultScreenHeight = 600;
    const SDL_Rect& defaultRect = { 0,0,100,100};
    const Offset& defaultOffset = {0,0,0,0};
    SigmaObject* obj;

    void SetUp() override {
        obj = new SigmaObject(defaultRect);
    }
    void TearDown() override {
        delete obj;
    }
};

#endif //SIGMAOBJECTFIXTURE_H
