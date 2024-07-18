//
// Created by thevi on 7/15/2024.
//

#include <Renderer/Dropdown.h>

#include "Renderer/ExtendableDropdownItem.h"

void Dropdown::handleEvent(const SDL_Event &e) {
    Button::handleEvent(e);
    if(dropdownActive) {
        for (auto item: items) {
            item->handleEvent(e);
        }
    }
}

void Dropdown::render(SDL_Renderer *renderer) {
    Button::render(renderer);

    if(dropdownActive) {
        for (auto item: items) {
            item->render(renderer);
        }
    }
}

void Dropdown::click() {
    dropdownActive = !dropdownActive;
    notifyOnClick();

    if(dropdownActive == false) {
        forceHideOfAnyChildren();
    }
}

void Dropdown::setAnchor(Anchor anchor) {
    Button::setAnchor(anchor);
}

void Dropdown::setRect(const SDL_Rect &rect) {
    Button::setRect(rect);
}

void Dropdown::setOffset(const Offset &offset) {
    Button::setOffset(offset);
}

void DropdownItem::setRenderingPriority(const int priority) {
    renderingPrority = priority;
    TLabel->setRenderingPriority(priority);
}


void Dropdown::addElement(std::shared_ptr<DropdownItem> item) {
    auto it = std::find_if(items.begin(), items.end(),
                          [&item](const std::shared_ptr<DropdownItem>& ptr) {
                              return ptr == item;
                          });

    if (it == items.end()) {  // Object not found
        int targetHeight = 0;
        for (const auto& i : items) {
            targetHeight += i->getHeight();
        }

        owner->removeRenderableObject(item.get());
        owner->removeEventObject(item.get());
        const SDL_Rect newRect = { currentRect.x, currentRect.y + currentRect.h + targetHeight, item->getWidth(), item->getHeight() };
        item->setRect(newRect);
        item->setRenderingPriority(renderingPrority);
        item->setItemOwner(this);
        items.push_back(item);
    } else {
        // skip
    }
}

void Dropdown::removeElement(std::shared_ptr<DropdownItem> item) {
    items.erase(std::remove_if(items.begin(), items.end(),
               [item](const std::shared_ptr<DropdownItem>& ptr) { return ptr == item; }),
               items.end());
}

void Dropdown::removeElement(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void Dropdown::forceHideOfAnyChildren() {
    for (auto i: items) {
        if (auto extendableItem = dynamic_cast<ExtendableDropdownItem*>(i.get())) {
            extendableItem->setIsExtended(false);
        }
    }
}







