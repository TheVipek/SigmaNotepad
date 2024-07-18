//
// Created by thevi on 7/15/2024.
//

#ifndef DROPDOWNITEM_H
#define DROPDOWNITEM_H
#include "Button.h"
class Dropdown;

class DropdownItem : public Button{

public:
    DropdownItem(SDL_Rect& rect, Window* _owner, const std::string& text)
       : Button(rect, _owner, text) {
    };
    ~DropdownItem() {
        itemOwner = nullptr;
    }
    bool operator==(const DropdownItem& other) const {
        return this == &other;
    }

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
    void setRect(const SDL_Rect& rect) override;
    void setAnchor(Anchor anchor) override;
    void setOffset(const Offset &offset) override;
    void setRenderingPriority(const int priority) override;
    virtual void setItemOwner(Dropdown* itemOwner) { this->itemOwner = itemOwner; }
protected:
    void click() override;
    Dropdown* itemOwner;
};

#endif //DROPDOWNITEM_H
