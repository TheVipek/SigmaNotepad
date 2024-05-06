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
    SigmaObject(SDL_Rect& rect)
        : rect(rect),offset(defaultOffset) {};

    virtual ~SigmaObject() = default;

    [[nodiscard]] int getX() const { return rect.x;}
    [[nodiscard]] int getY() const { return rect.y;}
    [[nodiscard]] int getWidth() const { return rect.w; }
    [[nodiscard]] int getHeight() const { return rect.h; }

    void setEnabled(const bool enabled) { this->enabled = enabled; }
    void setRect(const SDL_Rect& rect) { this->rect = rect;}
    void setVisibility(const bool visible) { this->visible = visible; }
    void setAnchor(Anchor anchor) { this->anchor = anchor; isAnchorDirty = true;}
    void setOffset(const Offset& offset) { this->offset = offset;  }
    void handlePosition(const int& screen_width, const int& screen_height);
    virtual void handleEvent(const SDL_Event& e) = 0;
protected:
    SDL_Rect&           rect;
    Anchor              anchor = Anchor::None;
    Offset&             offset;
    Offset              defaultOffset = Offset(0,0,0,0);
    bool                isAnchorDirty = true;
    bool                enabled = true;
    bool                visible = true;
};



#endif //SIGMAOBJECT_H
