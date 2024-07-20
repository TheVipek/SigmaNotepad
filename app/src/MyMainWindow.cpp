//
// Created by thevi on 6/18/2024.
//

#include "MyMainWindow.h"

#include <fstream>
#include <iomanip>
#include <thread>

#include "Renderer/ExtendableDropdownItem.h"


MyMainWindow::MyMainWindow(SDL_Window *_window, SDL_Renderer *_renderer, std::shared_ptr<WindowRenderingManager> mainWindow) : Window(_window, _renderer), mainWindow((mainWindow)) {


    currentFontSize = BASE_FONT_SIZE;
    currentZoom = BASE_ZOOM;
    //Creating GUI Elements
    SDL_Rect topPanelSize = {0, 0, 0, 25};
    topPanel = new Panel(topPanelSize, this);
    topPanel->setBackgroundColor({ 30, 30 ,30 ,255});
    topPanel->setAnchor(Anchor::FullWidthTop);

    SDL_Rect textEditSize = {0, 25, 0, 55};
    textEditField = new TextEdit(textEditSize, this);
    textEditField->setAnchor(Anchor::FullScreen);
    textEditField->setOffset({0,0,0,0});

    textEditField->setSize(currentFontSize * currentZoom);
    textEditField->setFontStyle(1);

    // SDL_Rect rect ={};
    // scrollLayout = new ScrollLayout(.2f, rect, this);
    // scrollLayout->assign(textEditField);

    SDL_Rect btnSize = {0, 0, 75, 25};
    fileDropdown = new Dropdown(btnSize, this, "File");
    fileDropdown->setAnchor(Anchor::TopLeft);
    fileDropdown->TLabel->setHorizontalAligment(HorizontalAligment::Center); // no implementation for text aligment
    fileDropdown->TLabel->setVerticalAligment(VerticalAligment::Center); // no implementation for text aligment
    fileDropdown->setRenderingPriority(-100);
    fileDropdown->setEventPriority(100);

    SDL_Rect fileItemRect = {0,0,75,25};
    auto fileItem1 = std::make_shared<DropdownItem>(fileItemRect, this, "Open");
    fileItem1->setAnchor(Anchor::TopLeft);
    fileItem1->registerOnClick([this]{ openFile(); });
    fileDropdown->addElement(fileItem1);

    auto fileItem2 = std::make_shared<DropdownItem>(fileItemRect, this, "Save");
    fileItem2->setAnchor(Anchor::TopLeft);
    fileItem2->registerOnClick([this]{ saveFile(); });
    fileDropdown->addElement(fileItem2);

    auto fileItem4 = std::make_shared<DropdownItem>(fileItemRect, this, "Exit");
    fileItem4->setAnchor(Anchor::TopLeft);
    fileItem4->registerOnClick([this]{ exit(); });
    fileDropdown->addElement(fileItem4);

    SDL_Rect btnSize2 = {75, 0, 75, 25};
    editDropdown = new Dropdown(btnSize2, this, "Edit");
    editDropdown->setAnchor(Anchor::TopLeft);
    editDropdown->setRenderingPriority(-100);
    editDropdown->setEventPriority(100);

    SDL_Rect editItemRect = {0,0,75,25};
    auto editItem1 = std::make_shared<ExtendableDropdownItem>(editItemRect, this, "Font");
    editItem1->setAnchor(Anchor::TopLeft);
    editDropdown->addElement(editItem1);
    SDL_Rect fontItemRect = {0,0,40,20};
    for (int i = 12; i <= 36; i+=4) {
        auto fontItem = std::make_shared<DropdownItem>(fontItemRect, this, std::to_string(i));
        fontItem->registerOnClick([this, i]{ updateFontSize(i);  });
        editItem1->addElement(fontItem);
    }




    SDL_Rect btnSize3 = {150, 0, 75, 25};
    showDropdown = new Dropdown(btnSize3, this, "Show");
    showDropdown->setAnchor(Anchor::TopLeft);
    showDropdown->setRenderingPriority(-100);
    showDropdown->setEventPriority(100);

    SDL_Rect showItemRect = {0,0,165,25};

    //Could implement something like 'Extendable DropdownItem' so after hovering it would show those two options
    auto showItem1 = std::make_shared<DropdownItem>(showItemRect, this, "Increase Zoom");
    showItem1->registerOnClick([this] {
        modifyZoom(ZOOM_STEP);
        updateFontSize(currentFontSize);
        updateZoomText(currentZoom);
    });
    showItem1->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(showItem1);

    auto showItem2 = std::make_shared<DropdownItem>(showItemRect, this, "Decrease Zoom");
    showItem2->registerOnClick([this] {
        modifyZoom(-ZOOM_STEP);
        updateFontSize(currentFontSize);
        updateZoomText(currentZoom);
    });

    showItem2->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(showItem2);


    //Could implement quick img displayer, so it would show arrow at right of it if its active
    auto showItem3 = std::make_shared<DropdownItem>(showItemRect, this, "Show Status Bar");
    showItem3->registerOnClick(std::bind(&MyMainWindow::changeVisibilityOfStatusBar, this));
    showItem3->setAnchor(Anchor::TopLeft);
    showDropdown->addElement(showItem3);


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

void MyMainWindow::openFile() {
    char const* filePatterns[] = { "*.txt" };
    char const * selection = tinyfd_openFileDialog(
        "Select file", // title
        "", // optional initial directory
        1, // number of filter patterns
        filePatterns,  // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
        NULL, // optional filter description
        0 // forbids multiple selections
    );

    if (selection) {
        std::ifstream file(selection, std::ios::binary | std::ios::ate);
        if (file) {
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (file.read(buffer.data(), size)) {
                // Convert the byte array to a string
                __gnu_cxx::rope<char> fileContents;
                fileContents.replace(0, 0, buffer.data(), size);
                textEditField->setText(fileContents);
                SDL_FlushEvents(0, 0xFFFF);
            } else {
                std::cerr << "Error reading the file." << std::endl;
            }
        } else {
            std::cerr << "Error opening the file." << std::endl;
        }
    }
}

void MyMainWindow::saveFile() {
    char const* filePatterns[]  = { "*.txt" };
    char const * saveFile = tinyfd_saveFileDialog(
    "Select file", // title
    "", // optional initial directory
    1, // number of filter patterns
    filePatterns,  // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
    NULL // optional filter description
    );

    if(saveFile) {
        std::ofstream file(saveFile, std::ios::binary); // Open file in binary write mode
        if (file) {
            rope<char> text = textEditField->getText(); // Assuming getText() returns the text content
            file.write(text.c_str(), text.size()); // Write text to file
            if (file.fail()) {
                std::cerr << "Error writing to the file." << std::endl;
            }
        } else {
            std::cerr << "Error opening the file for writing." << std::endl;
        }
    }
}

void MyMainWindow::exit() {
    SDL_Event quitEvent;
    quitEvent.type = SDL_QUIT;
    SDL_PushEvent(&quitEvent);
}

