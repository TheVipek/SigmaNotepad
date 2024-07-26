//
// Created by thevi on 7/26/2024.
//

#ifndef IINTERACTABLECOLORS_H
#define IINTERACTABLECOLORS_H
#include <SDL_pixels.h>

class IInteractableColors {
public:
    void setNormalColor(const SDL_Color c) { normalColor = c; }
    void setHoverColor(const SDL_Color c) { hoverColor = c; }
    void setClickColor(const SDL_Color c) { clickColor = c; }

protected:
    SDL_Color                   normalColor = { 16, 16, 16, 255};
    SDL_Color                   hoverColor = { 48, 48, 48, 255};;
    SDL_Color                   clickColor = { 64, 64, 64, 255};;
};


#endif //IINTERACTABLECOLORS_H
