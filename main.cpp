#include <iostream>

#define SDL_MAIN_HANDLED
#define main SDL_main
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "Managers/WindowRenderingManager.h"
#include "Renderer/Button.h"
#include "Renderer/Panel.h"
#include "Renderer/ScrollLayout.h"
#include "Renderer/TextEdit.h"

std::shared_ptr<WindowRenderingManager> mainWindow;
Panel* topPanel;
Button* fileButton;
Button* editButton;
Button* showButton;
TextEdit* textEditField;
ScrollLayout* scrollLayout;
Panel* bottomPanel;
TextLabel* bottomCounter;

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

    mainWindow->SetTargetWindow(window);
    mainWindow->SetTargetRenderer(renderer);

//Creating GUI Elements
    SDL_Rect topPanelSize = {0, 0, 0, 25};
    topPanel = new Panel(topPanelSize, mainWindow);
    topPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    topPanel->setAnchor(Anchor::FullWidthTop);


    SDL_Rect btnSize = {0, 0, 75, 25};
    fileButton = new Button(btnSize, mainWindow, "File");
    fileButton->setAnchor(Anchor::TopLeft);
    fileButton->TLabel->setHorizontalAligment(HorizontalAligment::Center);
    fileButton->TLabel->setVerticalAligment(VerticalAligment::Center);
    SDL_Rect btnSize2 = {0, 0, 75, 25};
    editButton = new Button(btnSize2, mainWindow, "Edit");
    editButton->setAnchor(Anchor::TopLeft);
    editButton->setOffset({100, 0,0,0});

    SDL_Rect btnSize3 = {0, 0, 75, 25};
    showButton = new Button(btnSize3, mainWindow, "Show");
    showButton->setAnchor(Anchor::TopLeft);
    showButton->setOffset({200, 0,0,0});

    SDL_Rect textEditSize = {0, 25, 0, 55};
    textEditField = new TextEdit(textEditSize, mainWindow);
    textEditField->setAnchor(Anchor::FullScreen);
    textEditField->setOffset({0,0,0,0});

    textEditField->setSize(64);
    textEditField->setFontStyle(1 | 2 | 3 | 4 | 5);

    SDL_Rect rect ={};
    scrollLayout = new ScrollLayout(.2f, rect, mainWindow);

    scrollLayout->assign(textEditField);

    SDL_Rect bottomPanelSize = {0, 0, 25, 30};
    bottomPanel = new Panel(bottomPanelSize, mainWindow);
    bottomPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    bottomPanel->setAnchor(Anchor::FullWidthBottom);

    SDL_Rect bottomCounterPanel = {0, 0, 0, 30};
    bottomCounter = new TextLabel(bottomCounterPanel, mainWindow);
    bottomCounter->setOffset({0,0,0,0});
    bottomCounter->setText("Current Text Length: 0");
    bottomCounter->setAnchor(Anchor::FullWidthBottom);

    textEditField->registerToOnTextLengthChanged([](int length) {
       bottomCounter->setText("Current Text Length: " + std::to_string(length));
    });

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
        SDL_Delay(4);
    }

    SDL_Quit();
    TTF_Quit();

    return 0;
}