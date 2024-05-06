//
// Created by thevi on 5/5/2024.
//

#include "Renderer/SigmaObject.h"

#include <iostream>

void SigmaObject::handlePosition(const int& screen_width, const int& screen_height) {
    switch (anchor) {
        case Anchor::None:
            break;
        case Anchor::Top:
            currentRect.x = ((screen_width - baseRect.w) / 2) ;
            currentRect.y = 0;
        break;
        case Anchor::TopLeft:
            currentRect.x = 0;
            currentRect.y = 0;
        break;
        case Anchor::TopRight:
            currentRect.x = screen_width - baseRect.w;
            currentRect.y = 0;
        break;
        case Anchor::BottomLeft:
            currentRect.x = 0;
            currentRect.y = screen_height - baseRect.h;
        break;
        case Anchor::BottomRight:
            currentRect.x = screen_width - baseRect.w;
            currentRect.y = screen_height - baseRect.h;
        break;
        case Anchor::Bottom:
            currentRect.x = ((screen_width - baseRect.w) / 2);
            currentRect.y = screen_height - baseRect.h;
        break;
        case Anchor::Left:
            currentRect.x = 0;
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::Right:
            currentRect.x = screen_width - baseRect.w;
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::Center:
            currentRect.x = ((screen_width - baseRect.w) / 2);
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::FullScreen:
            currentRect.w = screen_width + baseRect.w ;
            currentRect.h = screen_height + baseRect.h ;
            currentRect.x = baseRect.x;
            currentRect.y = baseRect.y;
        break;
        case Anchor::FullWidthTop:
            currentRect.w = screen_width;
            currentRect.x = 0;
            currentRect.y = 0;
        break;
        case Anchor::FullWidthCenter:
            currentRect.w = screen_width;
            currentRect.x = 0;
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::FullWidthBottom:
            currentRect.w = screen_width;
            currentRect.x = 0;
            currentRect.y = screen_height - baseRect.h;
        break;
        case Anchor::FullHeightLeft:
            currentRect.h = screen_height;
            currentRect.x = 0;
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::FullHeightCenter:
            currentRect.h = screen_height;
            currentRect.x = ((screen_width - baseRect.w) / 2);
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
        case Anchor::FullHeightRight:
            currentRect.h = screen_height;
            currentRect.x = screen_width - baseRect.w;
            currentRect.y = ((screen_height - baseRect.h) / 2);
        break;
    }
    currentRect.x += (offset.Left - offset.Right);
    currentRect.y += (offset.Bottom - offset.Top);
}
