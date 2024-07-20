//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMAOBJECT_H
#define SIGMAOBJECT_H

#include <SDL_events.h>
#include <SDL_rect.h>

#include "../IEventHandler.h"
#include "Offset.h"
#include "Window/Window.h"

enum class Anchor {
    TopLeft, TopRight, BottomLeft, BottomRight,
    Top, Bottom, Left, Right, Center,
    FullScreen,
    FullWidthTop, FullWidthCenter, FullWidthBottom,
    FullHeightLeft, FullHeightCenter, FullHeightRight,
    None
};

class SigmaObject : public IEventHandler {
public:
    SigmaObject(const SDL_Rect& rect, Window* owner)
        : baseRect(rect), currentRect(rect),offset(defaultOffset), owner(owner) {

    };


    virtual ~SigmaObject() = default;

    [[nodiscard]] int getX() const { return currentRect.x;}
    [[nodiscard]] int getY() const { return currentRect.y;}
    [[nodiscard]] int getWidth() const { return currentRect.w; }
    [[nodiscard]] int getHeight() const { return currentRect.h; }

    virtual void setEnabled(const bool enabled) { this->enabled = enabled; }
    virtual void setRect(const SDL_Rect& rect) { this->baseRect = rect; recalculatePosition(); }
    virtual void setVisibility(const bool visible) { this->visible = visible; }
    virtual bool getVisibility() { return this->visible; }
    virtual void setAnchor(Anchor anchor) { this->anchor = anchor; recalculatePosition(); }
    virtual void setOffset(const Offset& offset) { this->offset = offset; recalculatePosition(); }
    virtual void handlePosition(const int& screen_width, const int& screen_height);
    virtual void recalculatePosition();
    virtual void handleEvent(const SDL_Event& e) {
        setEventHandled(false);
        if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            recalculatePosition();
        }
    }
protected:
    SDL_Rect            currentRect;
    SDL_Rect            baseRect;
    Anchor              anchor = Anchor::None;
    Offset&             offset;
    Offset              defaultOffset = Offset(0,0,0,0);
    bool                enabled = true;
    bool                visible = true;
    Window* owner;
};



#endif //SIGMAOBJECT_H
