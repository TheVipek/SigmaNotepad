//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMAOBJECT_H
#define SIGMAOBJECT_H

#include <SDL_events.h>
#include <SDL_rect.h>
#include "Offset.h"

enum class Anchor {
    TopLeft, TopRight, BottomLeft, BottomRight,
    Top, Bottom, Left, Right, Center,
    FullScreen,
    FullWidthTop, FullWidthCenter, FullWidthBottom,
    FullHeightLeft, FullHeightCenter, FullHeightRight,
    None
};

class SigmaObject {
public:
    SigmaObject(const SDL_Rect& rect)
        : baseRect(rect), currentRect(rect),offset(defaultOffset) {};

    virtual ~SigmaObject() = default;

    [[nodiscard]] int getX() const { return currentRect.x;}
    [[nodiscard]] int getY() const { return currentRect.y;}
    [[nodiscard]] int getWidth() const { return currentRect.w; }
    [[nodiscard]] int getHeight() const { return currentRect.h; }

    virtual void setEnabled(const bool enabled) { this->enabled = enabled; }
    virtual void setRect(const SDL_Rect& rect) { this->currentRect = rect;}
    virtual void setVisibility(const bool visible) { this->visible = visible; }
    virtual void setAnchor(Anchor anchor) { this->anchor = anchor; isAnchorDirty = true;}
    virtual void setOffset(const Offset& offset) { this->offset = offset;  }
    virtual void handlePosition(const int& screen_width, const int& screen_height);
    virtual void handleEvent(const SDL_Event& e);
protected:
    SDL_Rect            currentRect;
    SDL_Rect            baseRect;
    Anchor              anchor = Anchor::None;
    Offset&             offset;
    Offset              defaultOffset = Offset(0,0,0,0);
    bool                isAnchorDirty = true;
    bool                enabled = true;
    bool                visible = true;
};



#endif //SIGMAOBJECT_H
