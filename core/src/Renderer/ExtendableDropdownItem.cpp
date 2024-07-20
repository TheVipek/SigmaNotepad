//
// Created by thevi on 7/17/2024.
//

#include "Renderer/ExtendableDropdownItem.h"

void ExtendableDropdownItem::handleEvent(const SDL_Event &e) {
    DropdownItem::handleEvent(e);
    setEventHandled(false);
    if(isExtended) {
        for (auto item: items) {
            item->handleEvent(e);

            if(item->isEventHandled()) {
                setEventHandled(true);
                break;
            }
        }
    }
}
void ExtendableDropdownItem::render(SDL_Renderer *renderer) {
    DropdownItem::render(renderer);

    if(isExtended) {
        for (auto item: items) {
            item->render(renderer);
        }
    }
}
void ExtendableDropdownItem::click() {
    //DropdownItem::click();
    Button::click();
    if(!isHovered) {
        if(isExtended)
            isExtended = false;
        return;
    }
    isExtended = !isExtended;
}
void ExtendableDropdownItem::addElement(std::shared_ptr<DropdownItem> item) {
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
        const SDL_Rect newRect = { baseRect.x + baseRect.w, baseRect.y + targetHeight, item->getWidth(), item->getHeight() };
        item->setRect(newRect);
        item->setRenderingPriority(renderingPrority);
        item->setEventHandled(eventPriority);
        item->setItemOwner(itemOwner);
        item->TLabel->setHorizontalAligment(this->TLabel->getHorizontalAligment());
        item->TLabel->setVerticalAligment(this->TLabel->getVerticalAligment());
        items.push_back(item);
    } else {
        // skip
    }
}
void ExtendableDropdownItem::removeElement(std::shared_ptr<DropdownItem> item) {
    items.erase(std::remove_if(items.begin(), items.end(),
                  [item](const std::shared_ptr<DropdownItem>& ptr) { return ptr == item; }),
                  items.end());
}
void ExtendableDropdownItem::removeElement(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void ExtendableDropdownItem::setItemOwner(Dropdown *itemOwner) {
    DropdownItem::setItemOwner(itemOwner);

    for (auto i: items) {
        i->setItemOwner(itemOwner);
    }
}


