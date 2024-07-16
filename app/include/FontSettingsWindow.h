//
// Created by thevi on 7/16/2024.
//

#ifndef FONTSETTINGSWINDOW_H
#define FONTSETTINGSWINDOW_H

#include "Window/Window.h"
#include <SDL2/SDL.h>

#include "Renderer/TextLabel.h"

class FontSettingsWindow : public Window {
public:

    FontSettingsWindow(SDL_Window* _window, SDL_Renderer* _renderer, int& fontToModify);
protected:
    TextLabel* fontSizeLabel;
    //Implement NumericText component
    int& fontToModify;
};
#endif //FONTSETTINGSWINDOW_H
