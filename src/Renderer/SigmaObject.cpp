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
            rect.x = ((screen_width - rect.w) / 2) ;
            rect.y = 0;
        break;
        case Anchor::TopLeft:
            rect.x = 0;
            rect.y = 0;
        break;
        case Anchor::TopRight:
            rect.x = screen_width - rect.w;
            rect.y = 0;
        break;
        case Anchor::BottomLeft:
            rect.x = 0;
            rect.y = screen_height - rect.h;
        break;
        case Anchor::BottomRight:
            rect.x = screen_width - rect.w;
            rect.y = screen_height - rect.h;
        break;
        case Anchor::Bottom:
            rect.x = ((screen_width - rect.w) / 2);
            rect.y = screen_height - rect.h;
        break;
        case Anchor::Left:
            rect.x = 0;
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::Right:
            rect.x = screen_width - rect.w;
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::Center:
            rect.x = ((screen_width - rect.w) / 2);
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::FullScreen:
            rect.w = screen_width;
            rect.h = screen_height;
            rect.x = 0;
            rect.y = 0;
        break;
        case Anchor::FullWidthTop:
            rect.w = screen_width;
            rect.x = 0;
            rect.y = 0;
        break;
        case Anchor::FullWidthCenter:
            rect.w = screen_width;
            rect.x = 0;
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::FullWidthBottom:
            rect.w = screen_width;
            rect.x = 0;
            rect.y = screen_height - rect.h;
        break;
        case Anchor::FullHeightLeft:
            rect.h = screen_height;
            rect.x = 0;
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::FullHeightCenter:
            rect.h = screen_height;
            rect.x = ((screen_width - rect.w) / 2);
            rect.y = ((screen_height - rect.h) / 2);
        break;
        case Anchor::FullHeightRight:
            rect.h = screen_height;
            rect.x = screen_width - rect.w;
            rect.y = ((screen_height - rect.h) / 2);
        break;
    }
    rect.x += (offset.Left - offset.Right);
    rect.y += (offset.Bottom - offset.Top);

}
