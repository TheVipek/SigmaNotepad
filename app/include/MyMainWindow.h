//
// Created by thevi on 6/18/2024.
//

#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <SDL2/SDL.h>
#include "Renderer/Button.h"
#include "Renderer/Panel.h"
#include "Renderer/ScrollLayout.h"
#include "Renderer/TextEdit.h"
#include "Renderer/TextLabel.h"
#include "Window/Window.h"

class MyMainWindow : public Window {
public:

    MyMainWindow(SDL_Window* _window, SDL_Renderer* _renderer);
protected:
    Panel* topPanel;
    Button* fileButton;
    Button* editButton;
    Button* showButton;
    TextEdit* textEditField;
    ScrollLayout* scrollLayout;
    Panel* bottomPanel;
    TextLabel* bottomCounter;

    void updateTextCounter(int length);

    void handleEvent(const SDL_Event &e) override;
    void renderFrame() override;
};



#endif //MYMAINWINDOW_H
