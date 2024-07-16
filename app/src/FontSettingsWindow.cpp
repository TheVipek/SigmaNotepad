//
// Created by thevi on 7/16/2024.
//

#include "FontSettingsWindow.h"
FontSettingsWindow::FontSettingsWindow(SDL_Window* _window, SDL_Renderer* _renderer, int& fontToModify)  : Window(_window, _renderer), fontToModify(fontToModify) {
    SDL_Rect fontLabelRect = {0, 0, 0, 25};
    fontSizeLabel = new TextLabel(fontLabelRect, this);
    fontSizeLabel->setText("Current Text Size:");
}