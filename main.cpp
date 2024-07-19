#include <iostream>

#define SDL_MAIN_HANDLED
#define main SDL_main
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "app/include/MyMainWindow.h"
#include "Managers/WindowRenderingManager.h"

std::shared_ptr<WindowRenderingManager> mainWindow;

std::shared_ptr<MyMainWindow> app;


int main(int argc, char* args[])
{
//Initialization
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

//Creating Window
    mainWindow = std::make_shared<WindowRenderingManager>();
    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    app = std::shared_ptr<MyMainWindow>(new MyMainWindow(window, renderer, mainWindow));
    mainWindow->addWindow(app);

    while(true) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                std::cout << "Exit";
                break;
            }
           mainWindow->handleEvent(event);
        }
        mainWindow->renderFrame();
        SDL_Delay(4);
    }

    SDL_Quit();
    TTF_Quit();

    return 0;
}
