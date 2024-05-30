//
// Created by thevi on 5/6/2024.
//

#ifndef IBACKGROUND_H
#define IBACKGROUND_H
#include <SDL_pixels.h>

class IBackground
{
public:
    void setBackgroundColor(const SDL_Color& color) {
        backgroundColor = color;
    }
protected:
    SDL_Color backgroundColor = { 25, 25, 25, 255};
};
#endif //IBACKGROUND_H
