//
// Created by thevi on 5/5/2024.
//

#include "Renderer/SigmaObject.h"

#include <iostream>

void SigmaObject::handleToAnchor(const int& width, const int& height) {
    switch (anchor) {
        case Anchor::None:
            break;
        case Anchor::Top:
            rect.x = ((width - rect.w) / 2) + baseX;;
            rect.y = 0 + baseY;
        break;
        case Anchor::TopLeft:
            rect.x = 0 + baseX;
            rect.y = 0 + baseY;
        break;
        case Anchor::TopRight:
            rect.x = width - rect.w + baseX;
            rect.y = 0 + baseY;
        break;
        case Anchor::BottomLeft:
            rect.x = 0 + baseX;
            rect.y = height - rect.h + baseY;
        break;
        case Anchor::BottomRight:
            rect.x = width - rect.w + baseX;
            rect.y = height - rect.h + baseY;
        break;
        case Anchor::Bottom:
            rect.x = ((width - rect.w) / 2) + baseX;
            rect.y = height - rect.h + baseY;
        break;
        case Anchor::Left:
            rect.x = 0 + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        break;
        case Anchor::Right:
            rect.x = width - rect.w + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        break;
        case Anchor::Center:
            rect.x = ((width - rect.w) / 2) + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        break;
        case Anchor::FullScreen:
            rect.w = width;
            rect.h = height;
            rect.x = 0 + baseX;
            rect.y = 0 + baseY;
        break;
        case Anchor::FullWidthTop:
            rect.w = width;
            rect.x = 0 + baseX;
            rect.y = 0 + baseY;
        break;
        case Anchor::FullWidthCenter:
            rect.w = width;
            rect.x = 0 + baseX;
            rect.y = (height / 2) - (rect.h / 2) + baseY;
        break;
        case Anchor::FullWidthBottom:
            rect.w = width;
            rect.x = 0 + baseX;
            rect.y = height - rect.h + baseY;
        break;
        case Anchor::FullHeightLeft:
            rect.h = height;
            rect.x = 0 + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        case Anchor::FullHeightCenter:
            rect.h = height;
            rect.x = ((width - rect.w) / 2) + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        case Anchor::FullHeightRight:
            rect.h = height;
            rect.x = ((width - rect.w) / 2) + baseX;
            rect.y = ((height - rect.h) / 2) + baseY;
        break;
    }
}
