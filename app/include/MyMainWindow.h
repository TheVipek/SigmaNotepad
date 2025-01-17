//
// Created by thevi on 6/18/2024.
//

#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <SDL2/SDL.h>

#include "Managers/WindowRenderingManager.h"
#include "Renderer/Button.h"
#include "Renderer/Dropdown.h"
#include "Renderer/Panel.h"
#include "Renderer/ScrollLayout.h"
#include "Renderer/TextEdit.h"
#include "Renderer/TextLabel.h"
#include "Window/Window.h"

#include "tinyfiledialogs.h"
#include "Renderer/ScrollLayoutText.h"

class MyMainWindow : public Window {
public:

    MyMainWindow(SDL_Window* _window, SDL_Renderer* _renderer, std::shared_ptr<WindowRenderingManager> mainWindow);
protected:
    std::shared_ptr<WindowRenderingManager> mainWindow;
    Panel* topPanel;
    Dropdown* fileDropdown;
    Dropdown* editDropdown;
    Dropdown* showDropdown;
    TextEdit* textEditField;
    ScrollLayoutText* scrollLayout;
    Panel* bottomPanel;
    TextLabel* bottomCounter;
    TextLabel* bottomZoom;

    const int BASE_FONT_SIZE = 12;
    int currentFontSize;

    const float BASE_ZOOM = 1.0f;
    float currentZoom;
    const float ZOOM_STEP = 0.25f;
    void updateTextCounter(int length);
    void updateZoomText(const float& zoom);
    void modifyZoom(float val);
    void updateFontSize(const int& size);
    void handleEvent(const SDL_Event &e) override;
    void renderFrame() override;
    void changeVisibilityOfStatusBar();


    void openFile();
    void saveFile();
    void exit();
};



#endif //MYMAINWINDOW_H
