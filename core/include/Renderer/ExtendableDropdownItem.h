//
// Created by thevi on 7/17/2024.
//

#ifndef EXTENDABLEDROPDOWNITEM_H
#define EXTENDABLEDROPDOWNITEM_H
#include "DropdownItem.h"
#include "IDropdownHolder.h"

class ExtendableDropdownItem : public DropdownItem, public IDropdownHolder {
public:
    ExtendableDropdownItem(SDL_Rect& rect, Window* _owner, const std::string& text)
       : DropdownItem(rect, _owner, text) {}

    bool operator==(const ExtendableDropdownItem& other) const {
        return this == &other;
    }

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;

    virtual void addElement(std::shared_ptr<DropdownItem> item);
    virtual void removeElement(std::shared_ptr<DropdownItem> item);
    virtual void removeElement(int index);
    virtual void setItemOwner(Dropdown *itemOwner) override;
    bool getIsExtended() const { return isExtended; }
    void setIsExtended(bool v) { isExtended = v; }
protected:
    bool isExtended = false;
    void click() override;
};

#endif //EXTENDABLEDROPDOWNITEM_H
