//
// Created by thevi on 7/15/2024.
//

#include "Renderer/Dropdown.h"

void DropdownItem::handleEvent(const SDL_Event &e) {
    Button::handleEvent(e);
}

void DropdownItem::render(SDL_Renderer *renderer) {
    Button::render(renderer);
}

void DropdownItem::onClick() {
    Button::onClick();
}

void DropdownItem::setAnchor(Anchor anchor) {
    Button::setAnchor(anchor);
}

void DropdownItem::setRect(const SDL_Rect &rect) {
    Button::setRect(rect);
}

void DropdownItem::setOffset(const Offset &offset) {
    Button::setOffset(offset);
}