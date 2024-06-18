//
// Created by thevi on 6/17/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <algorithm>
#include <SDL2/SDL.h>
#include <vector>
#include <ext/memory>

#include "IEventHandler.h"
#include "IRenderFrame.h"

class IRenderHandler;

class Window : public IEventHandler, public IRenderFrame {
public:
    Window(SDL_Window* _window, SDL_Renderer* _renderer) {
        window = std::shared_ptr<SDL_Window>(_window, SDL_DestroyWindow);
        renderer = std::shared_ptr<SDL_Renderer>(_renderer, SDL_DestroyRenderer);
    }
    ~Window() override = default;

    SDL_Renderer* getRenderer() { return renderer.get(); }
    SDL_Window* getWindow() { return window.get(); }

    void addRenderableObject(IRenderHandler* obj);
    void removeRenderableObject(IRenderHandler* obj);
    void addEventObject(IEventHandler* obj);
    void removeEventObject(IEventHandler* obj);
    virtual void handleEvent(const SDL_Event &e);
    virtual void renderFrame();

protected:
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Window> window;
    std::vector<IEventHandler*> eventHandlers;
    std::vector<IRenderHandler*> renderHandlers;
};

#endif //WINDOW_H
