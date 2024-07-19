//
// Created by thevi on 5/5/2024.
//

#include "Renderer/SigmaObject.h"

#include <iostream>
void SigmaObject::handlePosition(const int& screen_width, const int& screen_height) {
    currentRect.x = baseRect.x;
    currentRect.y = baseRect.y;

    int halfBaseWidth = baseRect.w / 2;
    int halfBaseHeight = baseRect.h / 2;
    int halfScreenWidth = screen_width / 2;
    int halfScreenHeight = screen_height / 2;

    switch (anchor) {
        case Anchor::None:
            break;
        case Anchor::TopLeft:
            break;
        case Anchor::Top:
            currentRect.x += halfScreenWidth - baseRect.w;
            break;
        case Anchor::TopRight:
            currentRect.x += screen_width - baseRect.w;
            break;
        case Anchor::BottomLeft:
            currentRect.y += screen_height - baseRect.h;
            break;
        case Anchor::Bottom:
            currentRect.x += halfScreenWidth - baseRect.w;
            currentRect.y += screen_height - baseRect.h;
            break;
        case Anchor::BottomRight:
            currentRect.x += screen_width - baseRect.w;
            currentRect.y += screen_height - baseRect.h;
            break;
        case Anchor::Left:
            currentRect.y += halfScreenHeight - baseRect.h;
            break;
        case Anchor::Right:
            currentRect.x += screen_width - baseRect.w;
            currentRect.y += halfScreenHeight - baseRect.h;
            break;
        case Anchor::Center:
            currentRect.x += halfScreenWidth - baseRect.w;
            currentRect.y += halfScreenHeight - baseRect.h;
            break;
        case Anchor::FullScreen:
            currentRect.w = screen_width - baseRect.w;
            currentRect.h = screen_height - baseRect.h;
            break;
        case Anchor::FullWidthTop:
            currentRect.w = screen_width;
            currentRect.h = baseRect.h;
            break;
        case Anchor::FullWidthCenter:
            currentRect.w = screen_width;
            currentRect.h = baseRect.h;
            currentRect.y += halfScreenHeight - baseRect.h;
            break;
        case Anchor::FullWidthBottom:
            currentRect.w = screen_width;
            currentRect.h = baseRect.h;
            currentRect.y += screen_height - baseRect.h;
            break;
        case Anchor::FullHeightLeft:
            currentRect.w = baseRect.w;
            currentRect.h = screen_height;
            break;
        case Anchor::FullHeightCenter:
            currentRect.w = baseRect.w;
            currentRect.h = screen_height;
            currentRect.x += halfScreenWidth - baseRect.w;
            break;
        case Anchor::FullHeightRight:
            currentRect.w = baseRect.w;
            currentRect.h = screen_height;
            currentRect.x += screen_width - baseRect.w;
            break;
    }

    currentRect.x += (offset.Left - offset.Right);
    currentRect.y += (offset.Bottom - offset.Top);
}
void SigmaObject::recalculatePosition() {
    if(owner != nullptr) {
        int w,h;
        if(SDL_GetRendererOutputSize(owner->getRenderer(), &w, &h) == 0) {
            handlePosition(w,h);
        }
    }
}

