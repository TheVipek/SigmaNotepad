//
// Created by thevi on 6/18/2024.
//

#include "MyMainWindow.h"

#include <iomanip>

#include "Renderer/ExtendableDropdownItem.h"

MyMainWindow::MyMainWindow(SDL_Window *_window, SDL_Renderer *_renderer, std::shared_ptr<WindowRenderingManager> mainWindow) : Window(_window, _renderer), mainWindow((mainWindow)) {


    currentFontSize = BASE_FONT_SIZE;
    currentZoom = BASE_ZOOM;

    // SDL_Window* fontSettingsWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 150, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // SDL_Renderer* fontSettingsRenderer = SDL_CreateRenderer(fontSettingsWindow, -1, SDL_RENDERER_ACCELERATED);
    // SDL_SetRenderDrawBlendMode(fontSettingsRenderer, SDL_BLENDMODE_BLEND);
    // fontSettings = std::shared_ptr<FontSettingsWindow>(new FontSettingsWindow(fontSettingsWindow, fontSettingsRenderer, currentFontSize));
    // mainWindow->addWindow(fontSettings);

    //Creating GUI Elements
    SDL_Rect topPanelSize = {0, 0, 0, 25};
    topPanel = new Panel(topPanelSize, this);
    topPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    topPanel->setAnchor(Anchor::FullWidthTop);


    SDL_Rect btnSize = {0, 0, 75, 25};
    fileDropdown = new Dropdown(btnSize, this, "File");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->TLabel->setHorizontalAligment(HorizontalAligment::Center); // no implementation for text aligment
    fileDropdown->TLabel->setVerticalAligment(VerticalAligment::Center); // no implementation for text aligment
    fileDropdown->setRenderingPriority(-100);

    SDL_Rect fileItemRect = {0,0,75,25};
    auto fileItem1 = new DropdownItem(fileItemRect, this, "Open");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->addElement(*fileItem1);

    auto fileItem2 = new DropdownItem(fileItemRect, this, "Save");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->addElement(*fileItem2);

    auto fileItem3 = new DropdownItem(fileItemRect, this, "Save As");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->addElement(*fileItem3);

    auto fileItem4 = new DropdownItem(fileItemRect, this, "Exit");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->addElement(*fileItem4);

    SDL_Rect btnSize2 = {75, 0, 75, 25};
    editDropdown = new Dropdown(btnSize2, this, "Edit");
    editDropdown->setAnchor(Anchor::TopLeft);
    editDropdown->setRenderingPriority(-100);

    SDL_Rect editItemRect = {0,0,75,25};
    auto editItem1 = new ExtendableDropdownItem(editItemRect, this, "Font");
    editItem1->setAnchor(Anchor::TopLeft);
    editDropdown->addElement(*editItem1);


    SDL_Rect fontItemRect = {0,0,50,25};
    for (int i = 0; i < 20; ++i) {
        auto fontItem = new DropdownItem(fontItemRect, this, std::to_string(i));
        editItem1->addElement(*fontItem);
    }




    SDL_Rect btnSize3 = {200, 0, 75, 25};
    showDropdown = new Dropdown(btnSize3, this, "Show");
    showDropdown->setAnchor(Anchor::TopLeft);
    showDropdown->setRenderingPriority(-100);

    SDL_Rect showItemRect = {0,0,75,25};

    //Could implement something like 'Extendable DropdownItem' so after hovering it would show those two options
    auto showItem1 = new DropdownItem(showItemRect, this, "Increase Zoom");
    showItem1->registerOnClick([this] {
        modifyZoom(ZOOM_STEP);
        updateFontSize(currentFontSize);
        updateZoomText(currentZoom);
    });
    showItem1->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(*showItem1);

    auto showItem2 = new DropdownItem(showItemRect, this, "Decrease Zoom");
    showItem2->registerOnClick([this] {
        modifyZoom(-ZOOM_STEP);
        updateFontSize(currentFontSize);
        updateZoomText(currentZoom);
    });

    showItem2->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(*showItem2);


    //Could implement quick img displayer, so it would show arrow at right of it if its active
    auto showItem3 = new DropdownItem(showItemRect, this, "Show Status Bar");
    showItem3->registerOnClick(std::bind(&MyMainWindow::changeVisibilityOfStatusBar, this));
    showItem3->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(*showItem3);




    SDL_Rect textEditSize = {0, 25, 0, 55};
    textEditField = new TextEdit(textEditSize, this);
    textEditField->setAnchor(Anchor::FullScreen);
    textEditField->setOffset({0,0,0,0});

    textEditField->setSize(currentFontSize * currentZoom);
    textEditField->setFontStyle(1 | 2 | 3 | 4 | 5);

    // SDL_Rect rect ={};
    // scrollLayout = new ScrollLayout(.2f, rect, this);
    // scrollLayout->assign(textEditField);



    SDL_Rect bottomPanelSize = {0, 0, 25, 30};
    bottomPanel = new Panel(bottomPanelSize, this);
    bottomPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    bottomPanel->setAnchor(Anchor::FullWidthBottom);

    SDL_Rect bottomCounterPanel = {0, 0, 250, 30};
    bottomCounter = new TextLabel(bottomCounterPanel, this);
    bottomCounter->setOffset({0,0,0,0});
    bottomCounter->setText("Current Text Length: 0");
    bottomCounter->setAnchor(Anchor::BottomLeft);

    textEditField->registerToOnTextLengthChanged(std::bind(&MyMainWindow::updateTextCounter, this, std::placeholders::_1));

    SDL_Rect bottomZoomPanel = {0, 0, 250, 30};
    bottomZoom = new TextLabel(bottomZoomPanel, this);
    bottomZoom->setOffset({0,0,0,0});
    bottomZoom->setVerticalAligment(VerticalAligment::Center); // no implementation for text aligment
    updateZoomText(currentZoom);

    bottomZoom->setAnchor(Anchor::BottomRight);
}

void MyMainWindow::updateZoomText(const float& zoom) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << zoom * 100;
    bottomZoom->setText("Current Zoom: " + oss.str() + "%");
}

void MyMainWindow::updateTextCounter(int length) {
    bottomCounter->setText("Current Text Length: " + std::to_string(length));
}

void MyMainWindow::modifyZoom(float val) {
    if(currentZoom + val > 0)
        currentZoom += val;
}

void MyMainWindow::updateFontSize(const int& size) {
    textEditField->setSize(size * currentZoom);
}

void MyMainWindow::changeVisibilityOfStatusBar() {
    bottomPanel->setVisibility(!bottomPanel->getVisibility());
    bottomCounter->setVisibility(!bottomCounter->getVisibility());
    bottomZoom->setVisibility(!bottomZoom->getVisibility());
}


void MyMainWindow::handleEvent(const SDL_Event &e) {
    if(e.type == SDL_MOUSEWHEEL) {
        if(SDL_GetModState() & KMOD_CTRL){
            int dir = e.wheel.y > 0 ? 1 : -1;
            int preZoom = currentZoom;
            modifyZoom(ZOOM_STEP * dir);
            if(currentZoom != preZoom) {
                updateFontSize(currentFontSize);
                updateZoomText(currentZoom);
            }
        }

    }
    Window::handleEvent(e);
}

void MyMainWindow::renderFrame() {
    Window::renderFrame();
}

