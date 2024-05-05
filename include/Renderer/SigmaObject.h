//
// Created by thevi on 4/30/2024.
//

#ifndef SIGMAOBJECT_H
#define SIGMAOBJECT_H

#include <SDL_events.h>
#include <SDL_rect.h>

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
        : rect(rect), baseX(rect.x), baseY(rect.y) {}

    virtual ~SigmaObject() = default;

    [[nodiscard]] int getX() const { return rect.x;}
    [[nodiscard]] int getY() const { return rect.y;}
    [[nodiscard]] int getWidth() const { return rect.w; }
    [[nodiscard]] int getHeight() const { return rect.h; }

    void setEnabled(const bool enabled) { this->enabled = enabled; }
    void setRect(const SDL_Rect& rect) { this->rect = rect;}
    void setVisibility(const bool visible) { this->visible = visible; }
    void setAnchor(Anchor anchor) { this->anchor = anchor; isAnchorDirty = true;}
    void handleToAnchor(const int& width, const int& height);
    virtual void handleEvent(const SDL_Event& e) = 0;
protected:


    SDL_Rect&           rect;

    Anchor              anchor = Anchor::None;
    int&                baseX;
    int&                baseY;

    bool                isAnchorDirty = true;
    bool                enabled = true;
    bool                visible = true;
};



#endif //SIGMAOBJECT_H
