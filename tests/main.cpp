//
// Created by thevi on 5/26/2024.
//
#define SDL_MAIN_HANDLED
#define main SDL_main
#include <SDL2/SDL.h>
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}