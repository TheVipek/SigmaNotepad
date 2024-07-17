//
// Created by thevi on 7/15/2024.
//
#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "Button.h"
#include "DropdownItem.h"
#include "IDropdownHolder.h"
#include "SigmaObject.h"
#include "SigmaRenderableObject.h"
#include "TextLabel.h"

class Dropdown : public Button, public IDropdownHolder {
public:
    Dropdown(SDL_Rect& rect, Window* _owner, const std::string& text)
       : Button(rect, _owner, text), IDropdownHolder()
    {}

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
    void setRect(const SDL_Rect& rect) override;
    void setAnchor(Anchor anchor) override;
    void setOffset(const Offset &offset) override;

    virtual void addElement(DropdownItem& item);
    virtual void removeElement(DropdownItem* item);
    virtual void removeElement(int index);

protected:

    bool                        dropdownActive = false;
    void click() override;
};

#endif //DROPDOWN_H
