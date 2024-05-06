#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include "Managers/WindowRenderingManager.h"
#include "Renderer/Button.h"
#include "Renderer/Panel.h"

std::shared_ptr<WindowRenderingManager> mainWindow;
int main(int argc, char *argv[])
{
//Initialization
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

//Creating Window
    mainWindow = std::make_shared<WindowRenderingManager>();

    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    mainWindow->SetTargetWindow(window);
    mainWindow->SetTargetRenderer(renderer);

//Creating GUI Elements
    SDL_Rect topPanelSize = {0, 0, 25, 25};
    auto panel = new Panel(topPanelSize, mainWindow);
    panel->setBackgroundColor({ 15, 25 ,35 ,255});
    panel->setAnchor(Anchor::FullHeightRight);

    SDL_Rect btnSize = {0, 0, 75, 25};
    auto btn = new Button(btnSize, mainWindow, "File");
    btn->setAnchor(Anchor::TopLeft);

    SDL_Rect btnSize2 = {0, 0, 75, 25};
    auto btn2 = new Button(btnSize2, mainWindow, "Edit");
    btn2->setAnchor(Anchor::TopLeft);
    btn2->setOffset({80, 0,0,0});

    SDL_Rect btnSize3 = {0, 0, 75, 25};
    auto btn3 = new Button(btnSize3, mainWindow, "Show");
    btn3->setAnchor(Anchor::TopLeft);
    btn3->setOffset({160, 0,0,0});

    while(true) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                std::cout << "Exit";
                break;
            }
            mainWindow->HandleEvent(event);
        }
        mainWindow->RenderFrame();
        SDL_Delay(16);
    }

    SDL_Quit();
    TTF_Quit();
    return 0;
}