//
// Created by thevi on 7/15/2024.
//

#include <Renderer/Dropdown.h>

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
    if(!isHovered) {
        if(dropdownActive)
            dropdownActive = false;
        return;
    }
    dropdownActive = !dropdownActive;
    notifyOnClick();
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


void Dropdown::addElement(DropdownItem& item) {
    auto it = std::find_if(items.begin(), items.end(),
                          [&item](const std::shared_ptr<DropdownItem>& ptr) {
                              return *ptr == item;
                          });

    if (it == items.end()) {  // Object not found
        int targetHeight = 0;
        for (const auto& i : items) {
            targetHeight += i->getHeight();
        }

        owner->removeRenderableObject(&item);
        owner->removeEventObject(&item);
        const SDL_Rect newRect = { currentRect.x, currentRect.y + currentRect.h + targetHeight, item.getWidth(), item.getHeight() };
        item.setRect(newRect);
        item.setRenderingPriority(renderingPrority);
        items.push_back(std::make_unique<DropdownItem>(item));
    } else {
        // skip
    }
}

void Dropdown::removeElement(DropdownItem* item) {
    items.erase(std::remove_if(items.begin(), items.end(),
               [item](const std::shared_ptr<DropdownItem>& ptr) { return ptr.get() == item; }),
               items.end());
}

void Dropdown::removeElement(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}








