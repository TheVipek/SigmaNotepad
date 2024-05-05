#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include "Managers/WindowRenderingManager.h"
#include "Renderer/Button.h"

std::shared_ptr<WindowRenderingManager> mainWindow;
Button* btn;
int main(int argc, char *argv[])
{
//Initialization
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

//Creating Window
    mainWindow = std::make_shared<WindowRenderingManager>();

    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    mainWindow->SetTargetWindow(window);
    mainWindow->SetTargetRenderer(renderer);

//Creating GUI Elements
    SDL_Rect btnSize = {100, 100, 200, 200};
    btn = new Button(btnSize, true, true, mainWindow, "hfgdhdfghdfg");
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