//
// Created by thevi on 6/18/2024.
//

#include "MyMainWindow.h"

#include <iomanip>

MyMainWindow::MyMainWindow(SDL_Window *_window, SDL_Renderer *_renderer) : Window(_window, _renderer) {

    currentFontSize = BASE_FONT_SIZE;
    currentZoom = BASE_ZOOM;
    //Creating GUI Elements
    SDL_Rect topPanelSize = {0, 0, 0, 25};
    topPanel = new Panel(topPanelSize, this);
    topPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    topPanel->setAnchor(Anchor::FullWidthTop);


    SDL_Rect btnSize = {0, 0, 75, 25};
    fileButton = new Button(btnSize, this, "File");
    fileButton->setAnchor(Anchor::TopLeft);
    fileButton->TLabel->setHorizontalAligment(HorizontalAligment::Center); // no implementation for text aligment
    fileButton->TLabel->setVerticalAligment(VerticalAligment::Center); // no implementation for text aligment
    SDL_Rect btnSize2 = {0, 0, 75, 25};
    editButton = new Button(btnSize2, this, "Edit");
    editButton->setAnchor(Anchor::TopLeft);
    editButton->setOffset({100, 0,0,0});

    SDL_Rect btnSize3 = {0, 0, 75, 25};
    showButton = new Button(btnSize3, this, "Show");
    showButton->setAnchor(Anchor::TopLeft);
    showButton->setOffset({200, 0,0,0});

    SDL_Rect textEditSize = {0, 25, 0, 55};
    textEditField = new TextEdit(textEditSize, this);
    textEditField->setAnchor(Anchor::FullScreen);
    textEditField->setOffset({0,0,0,0});

    textEditField->setSize(currentFontSize * currentZoom);
    textEditField->setFontStyle(1 | 2 | 3 | 4 | 5);

    SDL_Rect rect ={};
    scrollLayout = new ScrollLayout(.2f, rect, this);
    scrollLayout->assign(textEditField);


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

void MyMainWindow::updateZoomText(float zoom) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << zoom * 100;
    bottomZoom->setText("Current Zoom: " + oss.str() + "%");
}

void MyMainWindow::updateTextCounter(int length) {
    bottomCounter->setText("Current Text Length: " + std::to_string(length));
}

void MyMainWindow::modifyZoom(float val) {
    currentZoom += val;
}

void MyMainWindow::updateFontSize(int size) {
    textEditField->setSize(size * currentZoom);
}


void MyMainWindow::handleEvent(const SDL_Event &e) {
    if(e.type == SDL_MOUSEWHEEL) {
        if(SDL_GetModState() & KMOD_CTRL){
            int dir = e.wheel.y > 0 ? 1 : -1;
            if(currentZoom + (ZOOM_STEP * dir) > 0) {
                modifyZoom(ZOOM_STEP * dir);
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

