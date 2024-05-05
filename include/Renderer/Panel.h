//
// Created by thevi on 5/5/2024.
//

#ifndef PANEL_H
#define PANEL_H
#include "SigmaRenderableObject.h"


class Panel : public SigmaRenderableObject {
public:
    Panel(SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow) : SigmaRenderableObject(rect, targetWindow) {}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;

    void setBackgroundColor(const SDL_Color& color);
protected:
    SDL_Color backgroundColor = { 25, 25, 25, 255};
};

#endif //PANEL_H
