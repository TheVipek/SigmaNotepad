//
// Created by thevi on 6/18/2024.
//

#include "Window/Window.h"
#include "Renderer/IRenderHandler.h"
#include "Renderer/SigmaRenderableObject.h"

void Window::addRenderableObject(IRenderHandler* obj) {
    auto it = std::find(renderHandlers.begin(), renderHandlers.end(), obj);
    if (it == renderHandlers.end()) {  // Object not found
        renderHandlers.push_back(obj);
    } else {
        //skip
    }
}
void Window::removeRenderableObject(IRenderHandler* obj) {
    auto it = std::find(renderHandlers.begin(), renderHandlers.end(), obj);
    if (it == renderHandlers.end()) {  // Object not found
        //skip
    } else {
        renderHandlers.erase(it);
    }
}
void Window::addEventObject(IEventHandler* obj) {
    auto it = std::find(eventHandlers.begin(), eventHandlers.end(), obj);
    if (it == eventHandlers.end()) {  // Object not found
        eventHandlers.push_back(obj);
    } else {
        //skip
    }
}
void Window::removeEventObject(IEventHandler* obj) {
    auto it = std::find(eventHandlers.begin(), eventHandlers.end(), obj);
    if (it == eventHandlers.end()) {  // Object not found
        //skip
    } else {
        eventHandlers.erase(it);
    }
}
void Window::handleEvent(const SDL_Event &e) {
    for(const auto& obj : eventHandlers) {
        obj->handleEvent(e);
    }
}
void Window::renderFrame() {
    std::sort(renderHandlers.begin(), renderHandlers.end(), [](const IRenderHandler* a, const IRenderHandler* b) { return a->getRenderingPriority() > b->getRenderingPriority();});
    for(const auto& obj : renderHandlers)
    {
        obj->render(renderer.get());
    }
}