//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMAOBJECT_H
#define SIGMAOBJECT_H

#include <SDL_events.h>
#include <SDL_rect.h>
#include <string>

class SigmaObject {
public:
    SigmaObject(const int x, const int y, const int w, const int h, const bool enabled, const bool visible)
        : rect( {x,y,w,h} ), enabled(enabled), visible(visible) {}
    SigmaObject(const SDL_Rect& rect, const bool enabled, const bool visible)
        : rect(rect), enabled(enabled), visible(visible) {}
    virtual ~SigmaObject() = default;
    int getX() const { return rect.x;}
    int getY() const { return rect.y;}
    int getWidth() const { return rect.w; }
    int getHeight() const { return rect.h; }

    virtual void setEnabled(const bool enabled) { this->enabled = enabled; }
    virtual void setRect(const SDL_Rect& rect) { this->rect = rect; }
    virtual void setVisibility(const bool visible) { this->visible = visible; }


    virtual void handleEvent(const SDL_Event& e) = 0;
protected:
    SDL_Rect            rect;
    bool                enabled;
    bool                visible;
};



#endif //SIGMAOBJECT_H
