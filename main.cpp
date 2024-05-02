#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer/Button.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* windowSurface = NULL;
SDL_Surface* img = NULL;

Button* testBtn = NULL;
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    windowSurface = SDL_GetWindowSurface(window);

    SDL_Rect btnSize = {100, 100, 200, 200};
    testBtn = new Button(btnSize, true, true, *renderer, "hfgdhdfghdfg");

    testBtn->render();

    SDL_Delay(5000);
    // std::cout << "baeDir;" << SDL_GetBasePath();
    //
    // img = SDL_LoadBMP("assets/sigma.bmp");
    // if(img == NULL)
    // {
    //     std::cerr << "Error loading image: " << SDL_GetError() << std::endl;
    // }
    // else
    // {
    //     SDL_BlitScaled(img, NULL, windowSurface, NULL);
    //     SDL_UpdateWindowSurface(window);
    //     SDL_Delay(2000);
    // }



    // SDL_FreeSurface(img);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}