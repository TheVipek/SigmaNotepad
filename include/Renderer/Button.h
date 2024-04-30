//
// Created by thevi on 4/30/2024.
//



#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_rect.h>
#include <string>

class Button  {
    public:
    Button(int x, int y, int w, int h, const std::string& text);

    private:
    SDL_Rect rect;
};



#endif //BUTTON_H
